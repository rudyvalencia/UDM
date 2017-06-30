#include "stdafx.h"
CLimitSingleInstance g_SingleInstanceObj(_T("Global\\{F02204B2-BAA2-4282-8EAA24BCDE200AB2}"));

WNDCLASSEX msgWndClass = { 0 };
HWND msgWnd = nullptr;
NotifyIcon *ni = nullptr;

LRESULT CALLBACK msgWndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	IDispatcher* lpHandlerInstance = (IDispatcher*)
		GetWindowLong(hWnd, GWL_USERDATA);

	if (lpHandlerInstance == nullptr)
	{
		switch (msg)
		{
		case WM_CLOSE:
			DestroyWindow(hWnd);
			break;
		case WM_DESTROY:
			ni->Delete();
			PostQuitMessage(0);
			break;
		default:
			return DefWindowProc(hWnd, msg, wParam, lParam);
		}
	}
	else
	{
		// Black magic sanctioned by the ISO C++ standard.
		// 
		IDispatcher* dispatcher = dynamic_cast<IDispatcher*>
			((IDispatcher*) lpHandlerInstance);
		
		return dispatcher->WndProc(hWnd, msg, wParam, lParam);
	}
	
	return 0;
}

ULONGLONG GetDllVersion(LPCTSTR lpszDllName)
{
	ULONGLONG ullVersion = 0;
	HINSTANCE hinstDll;
	hinstDll = LoadLibrary(lpszDllName);
	if (hinstDll)
	{
		DLLGETVERSIONPROC pDllGetVersion;
		pDllGetVersion = (DLLGETVERSIONPROC)GetProcAddress(hinstDll, "DllGetVersion");
		if (pDllGetVersion)
		{
			DLLVERSIONINFO dvi;
			HRESULT hr;
			ZeroMemory(&dvi, sizeof(dvi));
			dvi.cbSize = sizeof(dvi);
			hr = (*pDllGetVersion)(&dvi);
			if (SUCCEEDED(hr))
				ullVersion = MAKEDLLVERULL(dvi.dwMajorVersion, dvi.dwMinorVersion, 0, 0);
		}
		FreeLibrary(hinstDll);
	}
	return ullVersion;
}

int APIENTRY _tWinMain(HINSTANCE instance, HINSTANCE prevInstance, LPTSTR cmdLine, int nCmdShow)
{
	if (g_SingleInstanceObj.IsAnotherInstanceRunning())
		return FALSE;

	ni = new NotifyIcon(instance);
	NOTIFYICONDATA data = { 0 };

	MSG msg = { 0 };
	BOOL bRet = FALSE;

	msgWndClass.cbSize = sizeof(WNDCLASSEX);
	msgWndClass.lpfnWndProc = msgWndProc;
	msgWndClass.hInstance = instance;
	msgWndClass.lpszClassName = MSGWND_CLASS;

	if (RegisterClassEx(&msgWndClass)) {
		msgWnd = CreateWindowEx(0, MSGWND_CLASS, _T("Message Window"), 0, 0, 0, 0, 0, HWND_MESSAGE, nullptr, nullptr, nullptr);


		data.cbSize = sizeof(NOTIFYICONDATA);
		data.uFlags = NIF_ICON | NIF_MESSAGE | NIF_TIP | NIF_INFO;
		data.hWnd = msgWnd;
		data.uID = ID_NOTIFYICON;
		data.uVersion = NOTIFYICON_VERSION_4;
		data.uCallbackMessage = MSG_NOTIFYICON;
		data.hIcon = (HICON)LoadImage(instance, MAKEINTRESOURCE(IDI_MAIN), IMAGE_ICON,
			GetSystemMetrics(SM_CXSMICON), GetSystemMetrics(SM_CYSMICON),
			LR_DEFAULTCOLOR);
		wcscpy_s(data.szTip, _T("UDM R1"));

		ni->SetData(data);

		if (!ni->Add(msgWnd)) {
			MessageBox(nullptr, _T("Unable to add Shell_NotifyIcon!"), APP_NAME, MB_ICONERROR | MB_OK);
			exit(EXIT_FAILURE);
		}

		// 
		// "Nervous? First-time?" - Old lady, "Airplane!"
		// 
		HKEY udmKey = nullptr;
		if (RegOpenKeyEx(HKEY_CURRENT_USER, APP_REG_KEY, 0, KEY_ALL_ACCESS, &udmKey) != ERROR_SUCCESS)
		{
			// 
			// Config key not found, create it and initialize default values
			// 
			RegCreateKey(HKEY_CURRENT_USER, APP_REG_KEY, &udmKey);
			RegSetValueEx(udmKey, SETTING_STANDBYTIME, 0, REG_DWORD, (const BYTE *)&DEFAULT_STANDBY, sizeof(DEFAULT_STANDBY));

			// 
			// Add autorun if it is allowed by the default configuration.
			// 
			HKEY userStartup = nullptr;
			RegOpenKeyEx(HKEY_CURRENT_USER, SYS_RUN_KEY, 0, KEY_ALL_ACCESS, &userStartup);
			
			if ((DEFAULT_START_ON_BOOT == 1) &&
				(RegGetValue(HKEY_CURRENT_USER, SYS_RUN_KEY,
				 APP_NAME, RRF_RT_REG_SZ, nullptr, nullptr, nullptr) != ERROR_SUCCESS))
			{
				TCHAR szFileName[MAX_PATH + 1];
				GetModuleFileName(nullptr, szFileName, MAX_PATH + 1);
				RegSetValueEx(userStartup, APP_NAME, 0, REG_SZ, (const BYTE *)&szFileName, MAX_PATH + 1);
				
				RegCloseKey(userStartup);
				RegSetValueEx(udmKey, SETTING_STARTONBOOT, 0, REG_DWORD, (const BYTE *)&DEFAULT_START_ON_BOOT, sizeof(DEFAULT_START_ON_BOOT));
			}

			// 
			// A little welcome popup
			// 
			data = ni->GetData();
			wcscpy_s(data.szInfoTitle, APP_NAME);
			wcscpy_s(data.szInfo, _T("Double-click to begin countdown; right-click for more options."));

			ni->SetData(data);
			ni->Modify();
		}
		RegCloseKey(udmKey);

		// 
		// Message loop
		// 
		while(GetMessage(&msg, NULL, 0, 0) > 0)
		{
			WNDPROC fWndProc = reinterpret_cast<WNDPROC>(GetWindowLong(msg.hwnd, GWL_WNDPROC));
			fWndProc(msg.hwnd, msg.message, msg.wParam, msg.lParam);
		}

		return msg.wParam;
	}
	else
	{
		// 
		// Holy failure mode, Batman!
		// 
		MessageBox(nullptr, _T("Unable to register message window!"), APP_NAME, MB_OK);
		return -1;
	}

	return 0;
}

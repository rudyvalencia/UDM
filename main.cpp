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

int WINAPI wWinMain(HINSTANCE instance, HINSTANCE prevInstance, PWSTR cmdLine, int nCmdShow)
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
		data.hIcon = LoadIcon(instance, MAKEINTRESOURCE(IDI_MAIN));
		data.uID = ID_NOTIFYICON;
		data.uVersion = NOTIFYICON_VERSION_4;
		data.uCallbackMessage = MSG_NOTIFYICON;
		wcscpy_s(data.szTip, _T("UDM R1"));
		LoadIconMetric(instance, MAKEINTRESOURCE(IDI_MAIN), LIM_SMALL, &data.hIcon);

		ni->SetData(data);

		if (!ni->Add(msgWnd)) {
			MessageBox(nullptr, _T("Unable to add Shell_NotifyIcon!"), APP_NAME, MB_ICONERROR | MB_OK);
			exit(EXIT_FAILURE);
		}
		
/*
		data = ni->GetData();
		wcscpy_s(data.szInfoTitle, APP_NAME);
		wcscpy_s(data.szInfo, _T("Running"));

		ni->SetData(data);
		ni->Modify();
*/
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

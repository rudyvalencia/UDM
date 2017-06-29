#include "stdafx.h"

NotifyIcon::NotifyIcon(HINSTANCE hInstance)
{
	instance = hInstance;
}

NotifyIcon::~NotifyIcon()
{
}

BOOL NotifyIcon::Add(HWND hWnd)
{
	SetWindowLong(hWnd, GWL_USERDATA, (long) this);
	return Shell_NotifyIcon(NIM_ADD, &data);
}

BOOL NotifyIcon::Modify()
{
	return Shell_NotifyIcon(NIM_MODIFY, &data);
}

BOOL NotifyIcon::Delete()
{
	return Shell_NotifyIcon(NIM_DELETE, &data);
}

BOOL NotifyIcon::SetFocus()
{
	return Shell_NotifyIcon(NIM_SETFOCUS, &data);
}

BOOL NotifyIcon::SetVersion()
{
	return Shell_NotifyIcon(NIM_SETVERSION, &data);
}

void NotifyIcon::SetData(NOTIFYICONDATA d)
{
	data = d;
}

NOTIFYICONDATA NotifyIcon::GetData()
{
	return data;
}

LRESULT CALLBACK NotifyIcon::WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	switch (msg)
	{
		case MSG_NOTIFYICON: {
			switch (lParam)
			{
			case WM_LBUTTONDBLCLK:
				wcscpy_s(data.szInfoTitle, _T("Info"));
				wcscpy_s(data.szInfo, _T("Double-clicked, exiting now"));
				data.hBalloonIcon = LoadIcon(nullptr, IDI_INFORMATION);

				Modify();

				SetTimer(hWnd, MSG_TIMER, 1000, nullptr);

				break;
			case WM_RBUTTONUP:
			case WM_CONTEXTMENU:
				ShowContextMenu(hWnd);
				break;
			}
		}
		break;

		case (MSG_EXIT):
			Delete();
			PostQuitMessage(0);
		break;

		case WM_TIMER:
			switch (wParam)
			{
				case MSG_TIMER:
					Delete();
					PostQuitMessage(0);

					return 0;
			}
		break;
		default:
			DefWindowProc(hWnd, msg, wParam, lParam);
		break;
	}

	// 
	// Do nothing.
	// 
	return 0;
}

void NotifyIcon::ShowContextMenu(HWND hWnd)
{
	POINT p;
	GetCursorPos(&p);

	HMENU udmMenu = GetSubMenu(LoadMenu(instance, MAKEINTRESOURCE(IDR_UDMMENU)), 0);

	SetForegroundWindow(hWnd);
	TrackPopupMenu(udmMenu, TPM_RIGHTBUTTON, p.x, p.y, 0, hWnd, nullptr);

	PostMessage(hWnd, WM_NULL, 0, 0);
	DestroyMenu(udmMenu);
}
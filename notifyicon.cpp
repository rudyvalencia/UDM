#include "stdafx.h"

NotifyIcon::NotifyIcon(RuntimeSupport& instance)
	: support(instance), data({ 0 })
{
}

NotifyIcon::~NotifyIcon()
{
}

BOOL NotifyIcon::Add(HWND hWnd)
{
	SetWindowLongPtr(hWnd, GWLP_USERDATA, (long) this);
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
	int wmId, wmEvent;

	switch (msg)
	{
		case MSG_NOTIFYICON: {
			switch (lParam)
			{
			case WM_LBUTTONDBLCLK:

				break;
			case WM_RBUTTONUP:
			case WM_CONTEXTMENU:
				ShowContextMenu(hWnd);
				break;
			}
		}
		break;

		case WM_COMMAND:
			wmId = LOWORD(wParam);
			wmEvent = HIWORD(wParam);

			switch (wmId)
			{
			case ID_UDM_DISPLAYSETTINGS:
				support.OpenDisplaySettings();
				break;
			case ID_UDM_PERSONALIZE:
				support.OpenPersonalization();
				break;
			case ID_UDM_EXIT:
				Delete();
				PostQuitMessage(0);
				break;
			}
			return 1;

		default:
			return DefWindowProc(hWnd, msg, wParam, lParam);
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

	HMENU udmMenu = GetSubMenu(LoadMenu(support.instance(), MAKEINTRESOURCE(IDR_UDMMENU)), 0);

	SetForegroundWindow(hWnd);
	TrackPopupMenu(udmMenu, TPM_RIGHTBUTTON, p.x, p.y, 0, hWnd, nullptr);

	PostMessage(hWnd, WM_NULL, 0, 0);
	DestroyMenu(udmMenu);
}
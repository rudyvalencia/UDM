#include "stdafx.h"

#define STRING LPTSTR

HINSTANCE RuntimeSupport::instance()
{
	return appInstance;
}

RuntimeSupport::RuntimeSupport()
	: refcount(0)
{
}

RuntimeSupport::RuntimeSupport(RuntimeSupport& reference)
	: refcount(reference.refcount)
{
	appInstance = reference.appInstance;
	reference.~RuntimeSupport();
}

void RuntimeSupport::SupportMessage()
{
	MessageBox(nullptr, _T("This application requires Windows 7 or newer."), APP_NAME, MB_ICONERROR | MB_OK);
	PostQuitMessage(EXIT_FAILURE);
}

void RuntimeSupport::startUp(HINSTANCE instance)
{
	GetWindowsDirectory(WinDir, MAX_PATH);
	astprintf(&ControlPath, _T("%s\\System32\\control.exe"), WinDir);

	version.dwOSVersionInfoSize = sizeof(OSVERSIONINFO);
	GetVersionEx(&version);

	// 
	// Compatibility:
	// 
	// * pre-Vista (< 6.0) - unsupported
	// * Vista (6.0) - unsupported
	// * Win7, 8, 8.1, 10 (> 6.0, 10.x) - supported
	//
	
	switch (version.dwMajorVersion) {
		case 10: 
		break;
		
		case 6: {
			switch (version.dwMinorVersion) {
				case 0:
					SupportMessage();
					break;
				
				default:
				break;
			}
		}
		break;
		
		default:
			SupportMessage();
			break;

	}
}

void RuntimeSupport::release()
{
	appInstance = nullptr;
	
	if (ControlPath != nullptr)
	{
		free(ControlPath);
	}
}

void RuntimeSupport::OpenDisplaySettings()
{
	switch (version.dwMajorVersion) {
		case 10:
			ShellExecute(0, 0, _T("ms-settings:display"), nullptr, nullptr, SW_SHOW);
			break;
		case 6:
			ShellExecute(0, 0, ControlPath, _T("/name Microsoft.Display /page Settings"), nullptr, SW_SHOW);
			break;
		default:
			ShellExecute(0, 0, ControlPath, _T("desk.cpl"), nullptr, SW_SHOW);
			break;
	}
}

void RuntimeSupport::OpenPersonalization()
{
	switch (version.dwMajorVersion) {
	case 10:
		ShellExecute(0, 0, _T("ms-settings:personalization-background"), nullptr, nullptr, SW_SHOW);
		break;
	case 6:
		ShellExecute(0, 0, ControlPath, _T("/name Microsoft.Personalization"), nullptr, SW_SHOW);
		break;
	default:
		ShellExecute(0, 0, ControlPath, _T("desk.cpl"), nullptr, SW_SHOW);
		break;
	}
}

void RuntimeSupport::AddRef()
{
	refcount++;
}

void RuntimeSupport::Release()
{
	refcount--;

	if (refcount == 0)
	{
		release();
	}
}

RuntimeSupport::~RuntimeSupport()
{
	release();
}

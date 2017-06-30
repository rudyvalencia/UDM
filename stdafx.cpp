#include <windows.h>
#include <tchar.h>

const wchar_t *APP_NAME = _T("UDM"),
			  *APP_REG_KEY = _T("Software\\Humanocentric\\UDM"),
			  *APP_MUTEXNAME = _T("Global\\UDMSingleton"),
			  *MSGWND_CLASS = _T("UDMMsgWnd");

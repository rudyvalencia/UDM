#include <windows.h>
#include <tchar.h>

const TCHAR *APP_NAME = _T("UDM"),
			*APP_REG_KEY = _T("Software\\Humanocentric\\UDM"),
			*APP_MUTEXNAME = _T("Global\\UDMSingleton"),
			*MSGWND_CLASS = _T("UDMMsgWnd"),
			*SYS_RUN_KEY = _T("Software\\Microsoft\\Windows\\CurrentVersion\\Run"),
			*SETTING_STANDBYTIME = _T("Standby"),
	        *SETTING_STARTONBOOT = _T("StartOnBoot");

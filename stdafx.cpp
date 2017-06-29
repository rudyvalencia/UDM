#include <windows.h>
#include <tchar.h>

const wchar_t *APP_NAME = _T("UDM"),
			  *APP_MUTEXNAME = _T("Global\\UDMSingleton"),
			  *MSGWND_CLASS = _T("UDMMsgWnd");

//
// Our app's GUID is {F02204B2-BAA2-4282-8EAA24BCDE200AB2}
//
GUID APP_GUID = { 0xF02204B2, 0xBAA2, 0x4282,{ 0x8E, 0xAA, 0x24, 0xBC, 0xDE, 0x20, 0x0A, 0xB2 } };

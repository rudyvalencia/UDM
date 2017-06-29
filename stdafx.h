#pragma once

#define NTDDI_VERSION NTDDI_WIN7
#define _WIN32_IE _WIN32_IE_IE80

#define WIN32_LEAN_AND_MEAN

#pragma comment(linker,"/manifestdependency:\"type='win32' name='Microsoft.Windows.Common-Controls' version='6.0.0.0' processorArchitecture='*' publicKeyToken='6595b64144ccf1df' language='*'\"")

// Windows API headers
#include <windows.h>
#include <versionhelpers.h>
#include <commctrl.h>
#include <shellapi.h>
#include <shlwapi.h>

// Standard C++ library headers
#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <stdarg.h>
#include <tchar.h>

// 
// Includes
// 
#include "resource.h"
#include "singleinstance.h"
#include "asprintf.h"
#include "dispatcher.h"
#include "notifyicon.h"

// 
// Global variables
// 

extern const TCHAR *APP_NAME,
					 *APP_MUTEXNAME,
					 *MSGWND_CLASS;

static const int ID_NOTIFYICON = 1,
				 MSG_NOTIFYICON = WM_USER;

// 
// Our app's GUID is {F02204B2-BAA2-4282-8EAA24BCDE200AB2}
//
static GUID APP_GUID;

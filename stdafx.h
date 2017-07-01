#pragma once

#define _WIN32_IE _WIN32_IE_IE60
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
#include "RuntimeSupport.h"
#include "singleinstance.h"
#include "asprintf.h"
#include "dispatcher.h"
#include "notifyicon.h"

// 
// Global variables
// 

extern const TCHAR *APP_NAME,
				   *APP_REG_KEY,
				   *APP_MUTEXNAME,
				   *MSGWND_CLASS,
				   *SYS_RUN_KEY,
				   *SETTING_STANDBYTIME,
				   *SETTING_STARTONBOOT;

static const DWORD DEFAULT_STANDBY = 30,
				   DEFAULT_START_ON_BOOT = 1;

static const int ID_NOTIFYICON = 1,
				 MSG_NOTIFYICON = WM_USER;

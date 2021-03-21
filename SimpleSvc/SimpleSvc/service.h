#pragma once

#include <windows.h>
#include "util.h"

#define SVCNAME TEXT("SimpleSvc")

// Forward declarations.
VOID WINAPI ServiceMain(DWORD, LPTSTR *);
VOID ServiceInit(void);
VOID ServiceStatus(DWORD, DWORD, DWORD);
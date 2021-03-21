#pragma once

#include <windows.h>
#include "util.h"

#define SVCNAME TEXT("SimpleSvc")

// Forward declarations.
VOID WINAPI ServiceMain(DWORD, LPTSTR *);
VOID ServiceInit(void);
VOID WINAPI ServiceCtrlHandler(DWORD);
DWORD WINAPI WorkerThread(LPVOID param);
VOID ServiceStatus(DWORD, DWORD, DWORD);
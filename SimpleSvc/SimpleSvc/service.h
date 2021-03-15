#pragma once

#include <windows.h>

#define SVCNAME TEXT("SimpleSvc")

// Forward declarations.
VOID WINAPI ServiceMain(DWORD, LPTSTR *);
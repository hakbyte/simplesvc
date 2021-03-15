#pragma once

#include <windows.h>
#include <strsafe.h>
#include "service.h"

// Buffer size for messages.
#define BUFSIZE 512 * sizeof(TCHAR)

// Forward declarations.
VOID LogEvent(const TCHAR*);

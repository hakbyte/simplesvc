#include "service.h"

//
// GLOBALS. Required for keeping the service state.
//
SERVICE_STATUS        gServiceStatus;
SERVICE_STATUS_HANDLE gStatusHandle;

//
// ServiceMain is entry point for our service.
//
VOID WINAPI ServiceMain(DWORD dwArgc, LPTSTR *lpszArgv)
{
    LogEvent(TEXT("Starting service"));

    // Register the handler function for the service.
    gStatusHandle = RegisterServiceCtrlHandler(SVCNAME, ServiceCtrlHandler);

    if (gStatusHandle != NULL)
    {
        // Default values (should always remain as set here).
        gServiceStatus.dwServiceType = SERVICE_WIN32_OWN_PROCESS;
        gServiceStatus.dwServiceSpecificExitCode = 0;

        // Report initial status to SCM.
        ServiceStatus(SERVICE_START_PENDING, NO_ERROR, 3000);
    }
}
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

        // Perform service-specific initialization and work.
        ServiceInit();

    }
}

//
// ServiceInit allocates any required resources and initializes the service.
//
VOID ServiceInit()
{
    // ???
}

//
// ServiceStatus updates our service status and reports it to SCM.
//
VOID ServiceStatus(DWORD dwCurrentState, DWORD dwWin32ExitCode, DWORD dwWaitHint)
{
    static DWORD dwCheckPoint = 1;

    // Update service status.
    gServiceStatus.dwCurrentState = dwCurrentState;
    gServiceStatus.dwWin32ExitCode = dwWin32ExitCode;
    gServiceStatus.dwWaitHint = dwWaitHint;

    switch (dwCurrentState)
    {
    case SERVICE_START_PENDING:
        gServiceStatus.dwControlsAccepted = 0;
        gServiceStatus.dwCheckPoint = dwCheckPoint++;
        break;

    case SERVICE_RUNNING:
        gServiceStatus.dwControlsAccepted = SERVICE_ACCEPT_STOP;
        gServiceStatus.dwCheckPoint = 0;
        break;

    case SERVICE_STOPPED:
        gServiceStatus.dwCheckPoint = 0;
        break;
    }

    // Report service status to SCM.
    SetServiceStatus(gStatusHandle, &gServiceStatus);
}

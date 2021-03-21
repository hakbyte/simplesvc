#include "service.h"

//
// GLOBALS. Required for keeping the service state.
//
SERVICE_STATUS        gServiceStatus;
SERVICE_STATUS_HANDLE gStatusHandle;
HANDLE                ghStopEvent = NULL;

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
// ServiceInit allocates any required resources and initializes our service.
//
VOID ServiceInit()
{
    // Create an event. The control handler function (ServiceCtrlHandler)
    // signals this event when it receives a stop control code.
    ghStopEvent = CreateEvent(NULL,  // default security attributes
                              TRUE,  // manual reset event
                              FALSE, // not signaled
                              NULL); // no name

    if (ghStopEvent == NULL)
    {
        ServiceStatus(SERVICE_STOPPED, NO_ERROR, 0);
        return;
    }

    // Report running status when initialization is complete.
    ServiceStatus(SERVICE_RUNNING, NO_ERROR, 0);

    // Perform work until service stops.
    HANDLE worker = CreateThread(NULL,         // security attributes
                                 0,            // initial size of the stack, in bytes
                                 WorkerThread, // function to be executed by the thread
                                 NULL,         // pointer to a variable to be passed to the thread
                                 0,            // thread creation flags 
                                 NULL);        // pointer to a variable that receives the thread identifier

    if (worker == NULL)
    {
        ServiceStatus(SERVICE_STOPPED, NO_ERROR, 0);
        return;
    }

    // Check whether to stop our service.
    WaitForSingleObject(ghStopEvent, INFINITE);
    ServiceStatus(SERVICE_STOPPED, NO_ERROR, 0);
}

//
// ServiceCtrlHandler is called by the SCM whenever a control code is sent to 
// our service using the ControlService function.
//
VOID WINAPI ServiceCtrlHandler(DWORD dwCtrlCode)
{
	// Handle requested control code. 
	switch (dwCtrlCode)
	{
	case SERVICE_CONTROL_STOP:
		ServiceStatus(SERVICE_STOP_PENDING, NO_ERROR, 0);

		// Signal service to stop.
		LogEvent(TEXT("Stopping service"));
		SetEvent(ghStopEvent);
		ServiceStatus(gServiceStatus.dwCurrentState, NO_ERROR, 0);
		LogEvent(TEXT("Service stopped"));
		break;

	case SERVICE_CONTROL_INTERROGATE:
		break;

	default:
		break;
	}
}

//
// WorkerThread.
//
DWORD WINAPI WorkerThread(LPVOID param)
{
	while (1)
	{
		Sleep(5000);
		LogEvent(TEXT("Doing some work..."));
	}

	return ERROR_SUCCESS;
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

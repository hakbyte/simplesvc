#include <windows.h>
#include "service.h"

//
// Entry point.
//
int main(DWORD dwArgc, TCHAR *lpszArgv[])
{
    SERVICE_TABLE_ENTRY DispatchTable[] =
    {
        { (LPSTR)SVCNAME, ServiceMain },
        { NULL, NULL }
    };

    // This call only returns when the service is stopped. 
    StartServiceCtrlDispatcher(DispatchTable);

    return 0;
}

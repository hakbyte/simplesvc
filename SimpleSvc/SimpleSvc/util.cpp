#include "util.h"

//
// LogEvent logs messages to the event log.
//
VOID LogEvent(const TCHAR* lpszMsg)
{
    LPCTSTR lpszLog[2];
    TCHAR   szData[BUFSIZE];
    HANDLE  hEventSource;

    // Get handle to the event log and post message.
    hEventSource = RegisterEventSource(NULL, SVCNAME);
    if (hEventSource != NULL)
    {
        // Format event log message.
        StringCchPrintf(szData, // destination buffer
            BUFSIZE,            // size of the destination buffer in characters
            TEXT("%s"),         // format string
            lpszMsg);           // arguments to be inserted into the format string

        lpszLog[0] = SVCNAME; 
        lpszLog[1] = szData;

        // Send mensage to event log (can be visualized with Event Viewer app).
        ReportEvent(hEventSource,      // event log handle
            EVENTLOG_INFORMATION_TYPE, // event type
            0,                         // event category
            0,                         // event identifier
            NULL,                      // no security identifier
            2,                         // size of lpszLog array
            0,                         // no binary data
            lpszLog,                   // array of strings
            NULL);                     // no binary data

        DeregisterEventSource(hEventSource);
    }
}
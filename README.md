# SimpleSvc
A bare bones Windows service. Adapted from [MSDN code](https://docs.microsoft.com/en-us/windows/desktop/Services/the-complete-service-sample) for learning purposes. 

# Installation

Install service:

```
C:\Windows\system32>sc create SimpleSvc binPath= Y:\Code\simplesvc\SimpleSvc\x64\Debug\SimpleSvc.exe type= own start= demand
[SC] CreateService SUCCESS

```

Start service:

```
C:\Windows\system32>sc start SimpleSvc

SERVICE_NAME: SimpleSvc
        TYPE               : 10  WIN32_OWN_PROCESS
        STATE              : 2  START_PENDING
                                (NOT_STOPPABLE, NOT_PAUSABLE, IGNORES_SHUTDOWN)
        WIN32_EXIT_CODE    : 0  (0x0)
        SERVICE_EXIT_CODE  : 0  (0x0)
        CHECKPOINT         : 0x0
        WAIT_HINT          : 0x7d0
        PID                : 17028
        FLAGS              :

```
Check Event Viewer Log:


Stop service:

```
C:\Windows\system32>sc stop SimpleSvc

SERVICE_NAME: SimpleSvc
        TYPE               : 10  WIN32_OWN_PROCESS
        STATE              : 1  STOPPED
        WIN32_EXIT_CODE    : 0  (0x0)
        SERVICE_EXIT_CODE  : 0  (0x0)
        CHECKPOINT         : 0x0
        WAIT_HINT          : 0x0
```

Delete service:

```
C:\Windows\system32>sc delete SimpleSvc
[SC] DeleteService SUCCESS
```
# SimpleSvc
A bare bones Windows service. Adapted from [MSDN code](https://docs.microsoft.com/en-us/windows/desktop/Services/the-complete-service-sample) for learning purposes. 

# Installation

Install service:

```
C:\>sc create SimpleSvc binPath= C:\SimpleSvc.exe type= own start= demand
[SC] CreateService SUCCESS

```

Start service:

```
C:\>sc start SimpleSvc

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
C:\>sc stop SimpleSvc

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
C:\>sc delete SimpleSvc
[SC] DeleteService SUCCESS
```
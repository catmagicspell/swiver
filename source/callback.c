#include <main.h>

int requestExit(int arg1, int arg2, void *common)
{
    sceKernelExitGame();
    return 0;
}

int callbackThread(SceSize args, void *argp)
{
    int callbackID = sceKernelCreateCallback("Exit Callback", requestExit, NULL);
    if (callbackID >= 0)
    {
        sceKernelRegisterExitCallback(callbackID);
        sceKernelSleepThreadCB();
    }
    return 0;
}

int setupExitCallback(void)
{
    int threadID = sceKernelCreateThread("Callback Thread", callbackThread, 0x11, 0xFA0, 0, 0);
    if (threadID >= 0)
        sceKernelStartThread(threadID, 0, 0);
    return threadID;
}
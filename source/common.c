#include <main.h>

int waitPress(int buttons)
{
    SceCtrlData pad;
    sceCtrlReadBufferPositive(&pad, 1);
    
    while (true)
    {
        if (pad.Buttons & buttons)
            return pad.Buttons & buttons;
        sceCtrlReadBufferPositive(&pad, 1);
    }
    return 0;
}

void waitRelease(int buttons)
{
    SceCtrlData pad;
    sceCtrlReadBufferPositive(&pad, 1);
    while (pad.Buttons & buttons)
        sceCtrlReadBufferPositive(&pad, 1);
}

void errorExit(char *fmt, ...)
{
    char msg[256];
    va_list list;
    va_start(list, fmt);
    vsprintf(msg, fmt, list);
    va_end(list);

    pspDebugScreenClear();
    setstc(RED);
    printf("%s\nPress X to exit.", msg);

    while (true)
    {
        SceCtrlData pad;
        sceCtrlReadBufferPositive(&pad, 1);
        if (pad.Buttons & PSP_CTRL_CROSS)
            sceKernelExitGame();
    }
}

void setrtc(void)
{
    srand(time(NULL));

    int red = rand() % 256;
    int green = rand() % 256;
    int blue = rand() % 256;
    int color = RGB(red, green, blue);

    setstc(color);
}

void printfs(int x, int y, int color, char *fmt, ...)
{
    char msg[256];
    va_list list;
    va_start(list, fmt);
    vsprintf(msg, fmt, list);
    va_end(list);

    setsxy(x, y);
    setstc(color);
    printf(msg);
}
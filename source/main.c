#include <main.h>

PSP_MODULE_INFO("swiver", 0x0800, MAJOR_VERSION, MINOR_VERSION);
PSP_MAIN_THREAD_ATTR(PSP_THREAD_ATTR_USER | PSP_THREAD_ATTR_VFPU);

void drawMenu(int index)
{
    pspDebugScreenClear();
    setstc(ORANGE);
    printf("swiver v%i.%i - github.com/catmagicspell/swiver\n\n", MAJOR_VERSION, MINOR_VERSION);
    setstc(WHITE);
    printf("Selected Version: %s\n", getVersionName(index));
    printf("Press L to decrease version, R to increase version.\n\n");
    printf("Press Cross to update version.txt with the selected version.\n");
    printf("Press Square to restore version.txt from the backup.\n");
    printf("Press Circle to exit the application.\n\n");
}

int main(void)
{
    setupExitCallback();
    pspDebugScreenInit();

    char result[512];
    int index = VERSION_620;

    setsxy(0, 0);
    setsbc(BLACK);
    drawMenu(index);

    while (true)
    {
        SceCtrlData pad;
        sceCtrlReadBufferPositive(&pad, 1);

        if (pad.Buttons & PSP_CTRL_RTRIGGER)
        {
            index++;
            if (index > VERSION_661)
                index = VERSION_100;

            drawMenu(index);
            sceKernelDelayThread(150000);
        }
        else if (pad.Buttons & PSP_CTRL_LTRIGGER)
        {
            index--;
            if (index < VERSION_100)
                index = VERSION_661;

            drawMenu(index);
            sceKernelDelayThread(150000);
        }

        if (pad.Buttons & PSP_CTRL_CROSS)
        {
            pspDebugScreenClear();
            printf("Assigning flash... ");
            initFlash();
            sceKernelDelayThread(1500000);
            setstc(ORANGE);
            printf("success!\n");
            setstc(WHITE);
            sceKernelDelayThread(500000);
            printf("Backing up current version.txt to flash1... ");
            copyFile("flash0:/vsh/etc/version.txt", "flash1:/vsh/version.txt.backup");
            sceKernelDelayThread(1500000);
            setstc(ORANGE);
            printf("success!\n");
            setstc(WHITE);
            sceKernelDelayThread(500000);
            printf("Writing %s version.txt to flash0... ", getVersionName(index));
            bin2File("ms0:/versionlist.txt.temp", versionlist, size_versionlist);
            convertVersion("ms0:/versionlist.txt.temp", index, result, sizeof(result));
            writeFile("flash0:/vsh/etc/version.txt", result, strlen(result));
            sceKernelDelayThread(1500000);
            setstc(ORANGE);
            printf("success!\n\n");
            setstc(WHITE);
            sceKernelDelayThread(500000);
            removeFile("ms0:/versionlist.txt.temp");
            printf("Exiting in 3 seconds...");
            sceKernelDelayThread(3000000);
            sceKernelExitGame();
        }

        if (pad.Buttons & PSP_CTRL_SQUARE)
        {
            pspDebugScreenClear();
            printf("Assigning flash... ");
            initFlash();
            sceKernelDelayThread(1500000);
            setstc(ORANGE);
            printf("success!\n");
            setstc(WHITE);
            sceKernelDelayThread(500000);
            printf("Restoring the previous version.txt... ");
            copyFile("flash1:/vsh/version.txt.backup", "flash0:/vsh/etc/version.txt");
            sceKernelDelayThread(1500000);
            setstc(ORANGE);
            printf("success!\n\n");
            setstc(WHITE);
            sceKernelDelayThread(500000);
            removeFile("flash1:/vsh/version.txt.backup");
            printf("Exiting in 3 seconds...");
            sceKernelDelayThread(3000000);
            sceKernelExitGame();
        }

        if (pad.Buttons & PSP_CTRL_CIRCLE)
        {
            printf("Exiting in 3 seconds...");
            sceKernelDelayThread(3000000);
            sceKernelExitGame();
        }

        sceDisplayWaitVblankStart();
    }

    return 0;
}
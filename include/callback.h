#ifndef CALLBACK_H
#define CALLBACK_H

int setupExitCallback(void);
int callbackThread(SceSize args, void *argp);
int requestExit(int arg1, int arg2, void *common);
#endif
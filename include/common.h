#ifndef COMMON_H
#define COMMON_H

void setrtc(void);
int waitPress(int buttons);
void waitRelease(int buttons);
void errorExit(char *fmt, ...);
void printfs(int x, int y, int color, char *fmt, ...);
#endif
#ifndef MAIN_H
#define MAIN_H
#pragma once

#include <pspsdk.h>
#include <pspctrl.h>
#include <pspiofilemgr.h>

#include <stdio.h>
#include <stdarg.h>
#include <stdbool.h>

#include <common.h>
#include <fileio.h>
#include <version.h>
#include <callback.h>

#define MAJOR_VERSION 1
#define MINOR_VERSION 0
#define BUFFER_SIZE 16 * 1024

#define printf pspDebugScreenPrintf
#define setsxy pspDebugScreenSetXY
#define setstc pspDebugScreenSetTextColor
#define setsbc pspDebugScreenSetBackColor

#define BLACK RGB(0, 0, 0)
#define GREEN RGB(0, 255, 0)
#define RED RGB(255, 0, 0)
#define WHITE RGB(255, 255, 255)
#define ORANGE RGB(255, 165, 0)
#define RGB(r, g, b) ((r) | ((g) << 8) | ((b) << 16))
#endif
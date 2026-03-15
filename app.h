#ifndef APP_H
#define APP_H

#include "app_comlib.h"

int AppInit(const int, const int, const int, const int);
void AppUpdate();
int AppQuit();

uint8_t AppRunning();

#endif
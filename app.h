#ifndef APP_H
#define APP_H

#include "common_libs.h"

int AppInit(const int, const int, const int, const int);
void AppUpdate();
int AppQuit();

bool AppRunning();

#endif
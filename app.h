#ifndef APP_H
#define APP_H

#include "common_libs.h"

struct AppStruct {
    SDL_Window* win;
    SDL_Renderer* rend;
    bool running;
};

extern struct AppStruct App;

int AppInit(const int, const int, const int);
void AppUpdate();
int AppQuit();

#endif
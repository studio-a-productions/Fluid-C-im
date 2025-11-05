#ifndef APP_H
#define APP_H
#include <SDL.h>
#include <stdio.h>
#include <stdbool.h>

extern bool AppRunning;

int AppInit(SDL_Window**, const int, const int);
void AppUpdate(SDL_Window**);
int AppQuit(SDL_Window**);

#endif
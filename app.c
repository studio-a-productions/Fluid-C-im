#include "app.h"
bool AppRunning = false;
int AppInit(SDL_Window** win, const int S_W, const int S_H) {
    if (AppRunning) {
        SDL_Log("AppInit Error: App is already running");
        return -1;
    }
    
    if (SDL_Init(SDL_INIT_EVERYTHING)) {
        SDL_Log("SDL_Init Error: %s\n", SDL_GetError());
        SDL_Quit();
        return -1;
    }
    *win = SDL_CreateWindow("Fluid Sim", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, S_W, S_H, SDL_WINDOW_SHOWN);
    if (!*win) {
        SDL_Log("SDL_Window Error %s\n", SDL_GetError());
        SDL_Quit();
        return -1;
    }
    AppRunning = true;
    return 0;
}

void AppUpdate(SDL_Window** win) {
    SDL_Event event;
    while(SDL_PollEvent(&event)) {
        switch (event.type) {
            case SDL_QUIT:
                AppRunning = false;
                break;
            case SDL_WINDOWEVENT_DISPLAY_CHANGED:
                // the window will automatically try to resize itself to not take up 100% of the screen
                // but only if the window/app mode is not fullscreen or supposed to be fullscreen
                break;
            default:
                break;
        }
    }
}

int AppQuit(SDL_Window** win) {
    if (AppRunning) {
        SDL_Log("AppQuit Error: App still running");
        return -1;
    }

    SDL_DestroyWindow(*win);
    *win = NULL;
    SDL_Quit();

    return 0;
}
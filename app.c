#include "app.h"

struct AppStruct App = { NULL, NULL, false };

int AppInit(const int S_W, const int S_H) {
    if (App.running) {
        SDL_Log("AppInit Error: App is already running");
        return -1;
    }
    
    if (SDL_Init(SDL_INIT_EVERYTHING)) {
        SDL_Log("AppInit Error w/ SDL_Init: %s\n", SDL_GetError());
        SDL_Quit();
        return -1;
    }
    App.win = SDL_CreateWindow("Fluid Sim", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, S_W, S_H, SDL_WINDOW_SHOWN);
    if (!App.win) {
        SDL_Log("AppInit Error w/ SDL_Window: %s\n", SDL_GetError());
        return -1;
    }
    App.rend = SDL_CreateRenderer(App.win, -1, SDL_RENDERER_ACCELERATED);
    if (!App.rend) {
        SDL_Log("AppUnit Error w/ SDL_Renderer: %s\n", SDL_GetError());
    }
    App.running = true;
    return 0;
}

void AppUpdate() {
    SDL_Event event;
    while(SDL_PollEvent(&event)) {
        switch (event.type) {
            case SDL_QUIT:
                App.running = false;
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

int AppQuit() {
    if (App.running) {
        SDL_Log("AppQuit Error: App still running");
        return -1;
    }
    
    if (App.win) SDL_DestroyWindow(App.win);
    if (App.rend) SDL_DestroyRenderer(App.rend);
    App.win = NULL;
    SDL_Quit();

    return 0;
}
#include "app.h"
#include "app_log.h"
#include "app_render.h"
#include "app_assets.h"
#include "app_comlib.h"
#include <SDL.h>

struct AppStruct {
    SDL_Window* win;
    DisplayRenderer rend;
    uint8_t running;
};

struct AppStruct App = { NULL, NULL, false };

int AppInit(const int S_WW, const int S_WH, const int S_CW, const int S_CH) {
    if (App.running) {
        AppLogError(LOG_INIT, "App is already running!");
        return -1;
    }
    
    if (SDL_Init(SDL_INIT_EVERYTHING)) {
        AppLogCrit(LOG_INIT, "SDL_Init failure: %s", SDL_GetError());
        return -1;
    }
    App.win = SDL_CreateWindow("Fluid Sim", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, S_WW, S_WH, SDL_WINDOW_SHOWN);
    if (!App.win) {
        AppLogCrit(LOG_INIT, "Window creation failure: %s", SDL_GetError());
        return -1;
    }

    DisplayRenderer renderer = {NULL, NULL, NULL};
    renderer.rend = SDL_CreateRenderer(App.win, -1, SDL_RENDERER_ACCELERATED);
    if (!renderer.rend) {
        AppLogCrit(LOG_GFX_INIT, "Renderer creation failure: %s", SDL_GetError());
        return -1;
    }
    if (AppCreateFrameBuffer(&renderer, S_CW, S_CH)) {
        AppLogCrit(LOG_GFX_INIT, "Couldn't create FrameBuffers!");
        return -1;
    }
    if (!renderer.mainTarget) {
        AppLogCrit(LOG_GFX_INIT, "Couldn't assign TargetFrameBuffer");
        return -1;
    }
    App.rend = renderer;
    App.running = 1U;
    return 0;
}

void AppUpdate() {
    SDL_Event event;
    while(SDL_PollEvent(&event)) {
        switch (event.type) {
            case SDL_QUIT:
                App.running = 0U;
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
        SDL_Log("AppQuit Error: App still running.\n");
        return -1;
    }

    if (AppDestroyFrameBuffer(&App.rend)) AppLogCrit(LOG_GFX_QUIT, "Couldn't destroy FrameBuffers");
    
    if (App.rend.rend) SDL_DestroyRenderer(App.rend.rend);
    else AppLogWarn(LOG_GFX_QUIT, "No renderer to destroy");
    if (App.win) SDL_DestroyWindow(App.win);
    else AppLogWarn(LOG_QUIT, "No window to destroy");

    App.win = NULL;

    SDL_Quit();
    return 0;
}

// dayum!!!
uint8_t AppRunning() {
    return App.running;
}
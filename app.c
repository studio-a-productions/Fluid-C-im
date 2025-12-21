#include "app.h"
#include "app_render.h"
#include "app_assets.h"

struct AppStruct {
    SDL_Window* win;
    DisplayRenderer rend;
    bool running;
};

struct AppStruct App = { NULL, NULL, false };

int AppInit(const int S_WW, const int S_WH, const int S_CW, const int S_CH) {
    if (App.running) {
        SDL_Log("AppInit Error: App is already running");
        return -1;
    }
    
    if (SDL_Init(SDL_INIT_EVERYTHING)) {
        SDL_Log("AppInit Error w/ SDL_Init: %s\n", SDL_GetError());
        return -1;
    }
    App.win = SDL_CreateWindow("Fluid Sim", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, S_WW, S_WH, SDL_WINDOW_SHOWN);
    if (!App.win) {
        SDL_Log("AppInit Error w/ SDL_Window: %s\n", SDL_GetError());
        return -1;
    }

    DisplayRenderer renderer = {NULL, NULL, NULL};
    renderer.renderTarget = SDL_CreateRenderer(App.win, -1, SDL_RENDERER_ACCELERATED);
    if (!renderer.renderTarget) {
        SDL_Log("AppInit Error w/ SDL_Renderer: %s\n", SDL_GetError());
        return -1;
    }
    if (AppCreateFrameBuffer(&renderer, S_CW, S_CH)) {
        SDL_Log("AppInit Error: couldn't create frame buffers!\n");
        return -1;
    }
    if (!renderer.frontFrame) {
        SDL_Log("AppInit Error: frame buffer not assigned!\n");
        return -1;
    }
    App.rend = renderer;
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
        SDL_Log("AppQuit Error: App still running.\n");
        return -1;
    }

    AppDestroyFrameBuffer(&App.rend);
    
    if (App.rend.renderTarget) SDL_DestroyRenderer(App.rend.renderTarget);
    else SDL_Log("APP_QUIT: No Renderer to destroy \n");
    if (App.win) SDL_DestroyWindow(App.win);
    else SDL_Log("APP_QUIT: No Window to destroy\n");

    App.win = NULL;

    SDL_Quit();
    return 0;
}

// dayum!!!
bool AppRunning() {
    return App.running;
}
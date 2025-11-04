#include <stdio.h>
#include <stdbool.h> /* optional, can be removed */
#include <SDL.h>

// initial window size
#define W_W 800
#define W_H 600
// constant canvas size
#define CANVAS_W 200
#define CANVAS_H 150

bool running = true;

inline void Update() {
    SDL_Event event;
    while(SDL_PollEvent(&event)) {
        switch (event.type) {
            case SDL_WINDOWEVENT_CLOSE:
                running = false;

                break;
        }
    }
}
int SDL_main(int argc, char *argv[]) {
    if (SDL_Init(SDL_INIT_EVERYTHING)) {
        SDL_Log("SDL_Init Error: %s\n", SDL_GetError());
        SDL_Quit();
        return -1;
    }
    SDL_Window* win = SDL_CreateWindow("Fluid Sim", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, W_W, W_H, SDL_WINDOW_SHOWN);
    if (!win) {
        SDL_Log("SDL_Window Error %s\n", SDL_GetError());
        SDL_Quit();
        return -1;
    }

    while (running) {
        Update();
    }

    SDL_Quit();
}
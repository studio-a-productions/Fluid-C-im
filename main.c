#include "app.h"

// initial window size
#define W_W 800
#define W_H 600
// canvas size
#define CANVAS_W 200
#define CANVAS_H 150

void UpdateDisplay();

int main(int argc, char *argv[]) {
    SDL_Window* win = NULL;

    if(AppInit(&win, W_W, W_H)) {
        SDL_Quit();
        exit(-1);
    }

    while (AppRunning) {
        AppUpdate(&win);
    }

    if (AppQuit(&win)) {
        SDL_Quit();
        exit(-1);
    }

    return 0;
}


void UpdateDisplay() {

}


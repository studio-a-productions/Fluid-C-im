#include "app.h"

// initial window size
// we're doing a 8:6/4:3 ratio to match the CANVAS (render texture)
#define W_W 800
#define W_H 600
// canvas size
#define CANVAS_W 200
#define CANVAS_H 150

extern struct AppStruct App;

void UpdateDisplay();

int main(int argc, char *argv[]) {
    if(AppInit(W_W, W_H)) {
        if (AppQuit()) SDL_Quit();
        return 1;
    }

    while (App.running) {
        AppUpdate();
    }

    if (AppQuit()) {
        SDL_Quit();
        return 1;
    }

    return 0;
}

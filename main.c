#include "common_libs.h"
#include "app.h"
#include "cim.h"

// initial window size
// we're doing a 8:6/4:3 ratio to match the CANVAS
#define W_W 800
#define W_H 600
// canvas size (upscale 4)
#define CANVAS_W 200
#define CANVAS_H 150

#define PARTICLE_BUFFER_S 100

void UpdateDisplay();

static inline int freeResources(const int exit_c) {
    if (CimQuit()) {
        if (AppQuit()) SDL_Quit();
        exit(2); // very bad :/
    }
    if (AppQuit()) {
        SDl_Quit();
        return 1;
    }
    return exit_c;
}

int main(int argc, char *argv[]) {
    if(AppInit(W_W, W_H, PARTICLE_BUFFER_S)) {
        return freeResources(1);
    }
    else if (CimInit(100)) {
        return freeResources(1);
    }

    while (App.running) {
        AppUpdate();
    }

    return freeResources(0);
}

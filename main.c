#include "common_libs.h"
#include "app.h"

#include "cim.h"
#include "cim_error.h" // to handle errors

// initial window size
// we're doing a 8:6/4:3 ratio to match the CANVAS
#define W_W 800
#define W_H 600
// canvas size (upscale 4)
#define CANVAS_W 200
#define CANVAS_H 150

#define PARTICLE_BUFFER_S 100

static inline int freeResources(const int exit_c) {
    if (CimQuit()) {
        if (AppQuit()) SDL_Quit();
        return 2; // very bad :/
    }
    else if (AppQuit()) {
        SDL_Quit();
        return 1;
    } else return exit_c;
}

int main(int argc, char *argv[]) {

    if (Cim_Init != CIM_INIT)
        return CIM_ERROR;

    while (AppRunning()) {
        AppUpdate();
    }

    return freeResources(0);
}

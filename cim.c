#include "cim.h"
#include "cim_particle.h"
#include "common_libs.h"

int CimInit(int pBuffSize) {
    if (InitCimPBuffer(pBuffSize)) {
        SDL_Log("CimInit Failed!");
        return -1;
    }


    return 0;
};

int CimQuit() {
    if (FreeCimPBuffer()) {
        SDL_Log("CimExit Failed!");
        return -1;
    }

    return 0;
}
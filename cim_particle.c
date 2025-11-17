#include "cim_particle.h"

struct particleBuffer cimPBuffer = {NULL, NULL, NULL, NULL, NULL, 0, 0};

int InitCimPBuffer(int icapacity) {
    if (!icapacity) {
        SDL_Log("InitCimBuffer Error: no initial capacity given.\n");
        return -1;
    }
    else if (icapacity < 0) {
        SDL_Log("InitCimPBuffer Error: a buffer capacity cannot be negative.\n");
        return -1;
    }
    cimPBuffer.x = SDL_malloc(sizeof(float) * icapacity);
    if (!cimPBuffer.x) {
        SDL_Log("InitCimPBuffer Error w/ x-pos buffer.\n");
        return -1;
    }
    cimPBuffer.y = SDL_malloc(sizeof(float) * icapacity);
    if (!cimPBuffer.y) {
        SDL_Log("InitCimPBuffer Error w/ y-pos buffer.\n");
        return -1;
    }
    cimPBuffer.vx = SDL_malloc(sizeof(float) * icapacity);
    if (!cimPBuffer.vx) {
        SDL_Log("InitCimPBuffer Error w/ x-veloc buffer.\n");
        return -1;
    }
    cimPBuffer.vy = SDL_malloc(sizeof(float) * icapacity);
    if (!cimPBuffer.vy) {
        SDL_Log("InitCimPBuffer Error w/ y-veloc buffer.\n");
        return -1;
    }
    cimPBuffer.type = SDL_malloc(sizeof(int) * icapacity);
    if (!cimPBuffer.type) {
        SDL_Log("InitCimPBuffer Error w/ y-veloc buffer.\n");
        return -1;
    }
    cimPBuffer.capacity = icapacity;
    return 0;

}

int FreeCimPBuffer() {
    if (cimPBuffer.x) SDL_free(cimPBuffer.x);
    if (cimPBuffer.y) SDL_free(cimPBuffer.y);
    if (cimPBuffer.vx) SDL_free(cimPBuffer.vx);
    if (cimPBuffer.vy) SDL_free(cimPBuffer.vy);
    if (cimPBuffer.type) SDL_free(cimPBuffer.type);

    cimPBuffer.x = cimPBuffer.y = cimPBuffer.vx = cimPBuffer.vy = NULL;
    cimPBuffer.type = NULL;
    cimPBuffer.capacity = cimPBuffer.used = 0;

    return 0;
}
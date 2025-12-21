#include "app_render.h"

int AppCreateFrameBuffer(DisplayRenderer*curRenderer, const int S_W, const int S_H) {
    if (!curRenderer->renderTarget) {
        SDL_Log("APP_RENDER: No Renderer Present!\n");
        return -1;
    }
    if (curRenderer->frontFrame) {
        SDL_Log("APP_RENDER: frame buffer already present");
        return -1;
    }
    // (SDL_PIXELFORMAT && SDL_TEXTUREACCESS can/might be changed here)
    curRenderer->frontFrame = SDL_CreateTexture(curRenderer->renderTarget, 
        SDL_PIXELFORMAT_RGB24, SDL_TEXTUREACCESS_STREAMING, S_W, S_H); 

    return 0;
}

int AppDestroyFrameBuffer(DisplayRenderer*curRenderer) {
    if (!curRenderer->renderTarget) {
        SDL_Log("APP_RENDER: No Renderer Present!\n");
        return -1;
    } 
    if (curRenderer->frontFrame) {
        SDL_DestroyTexture(curRenderer->frontFrame);
    } else SDL_Log("APP_RENDER: No frame buffer to destroy");
    
    return 0;
}
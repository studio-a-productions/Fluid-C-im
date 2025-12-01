#include "app_render.h"

int AppCreateFrameBuffers(DisplayRenderer*curRenderer, const int S_W, const int S_H) {
    if (!curRenderer->renderTarget) {
        SDL_Log("APP_RENDER: No Renderer Present!\n");
        return -1;
    }
    if (curRenderer->backFrame || curRenderer->frontFrame) {
        SDL_Log("APP_RENDER: frame buffer(s) already present");
        return -1;
    }
    curRenderer->backFrame = NULL; // TODO: ADD SDL_CreateTexture() for canvas
    curRenderer->frontFrame = NULL; // TODO: ADD SDL_CreateTexture() for canvas

    return 0;
}

int AppDestroyFrameBuffers(DisplayRenderer*curRenderer) {
    // TODO: free(life)
    
    return 0;
}
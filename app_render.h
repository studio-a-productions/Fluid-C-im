#ifndef APP_RENDER_H
#define APP_RENDER_H
#include "common_libs.h"

typedef struct {
    SDL_Texture* frontFrame;
    SDL_Texture* backFrame;
    SDL_Renderer* renderTarget;
} DisplayRenderer;

int AppCreateFrameBuffers(DisplayRenderer* curRenderer, const int S_W, const int S_H);
int AppDestroyFrameBuffers(DisplayRenderer*curRenderer);

void AppRenderTexture(DisplayRenderer* curRenderer, SDL_Texture* target, bool scale);
void AppRenderTextureAt(DisplayRenderer* curRenderer, const int x, const int y, SDL_Texture* texture);
void AppRenderInstances(DisplayRenderer* curRenderer, const int*x, const int*y, SDL_Texture);


#endif
#ifndef APP_RENDER_H
#define APP_RENDER_H
#include "common_libs.h"

typedef struct {
    SDL_Texture* frontFrame;
    SDL_Renderer* renderTarget;
} DisplayRenderer;

enum size_modes {
    SIZE_NONE,
    SIZE_PROPORTIONAL,
    SIZE_RELATIVE
};

int AppCreateFrameBuffer(DisplayRenderer* curRenderer, const int S_W, const int S_H);
int AppDestroyFrameBuffer(DisplayRenderer*curRenderer);

void AppRenderTexture(DisplayRenderer* curRenderer, SDL_Texture* target, uint8_t size_mode);
void AppRenderTextureAt(DisplayRenderer* curRenderer, const int x, const int y, SDL_Texture* texture, uint8_t size_mode);
void AppRenderInstances(DisplayRenderer* curRenderer, const int*x, const int*y, SDL_Texture* texture, uint8_t size_mode);


#endif
#ifndef APP_ASSETS_H
#define APP_ASSETS_H

#include "common_libs.h"

typedef struct {
    // This will be the asset attribute pointer/empty, easy?
    int a;
} app_asset;

int CreateTextureAtlas(const char*, const int*); // takes a string and an array of ints. The array of ints signals the size of each texture
int CreateTextureAtlasFDir(const char*); // single path

#endif
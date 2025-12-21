#ifndef APP_ASSETS_H
#define APP_ASSETS_H

#include "common_libs.h"

typedef struct {
    // This will be the asset attribute pointer/empty, easy?
    int a;
} app_asset;

int CreateTextureAtlas(const char*); // takes a path and an array of ints.

#endif
#ifndef RAY_CAST_PARAMS_H
#define RAY_CAST_PARAMS_H
#include <SDL2/SDL.h>
typedef struct raycast_params{
    SDL_PixelFormat* format;
    struct world* w;
    Uint32* pixels;
    int width;
    int height;
    float screen_scale;
    struct camera* cam;
    //pointers to the corners of the screen
    float topDir[3];
    float rightDir[3];
    float botLeftCorner[3];
    
    int shadow;
    int reflection;
} raycast_params;

#endif

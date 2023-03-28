#ifndef RAY_CAST_PARAMS_H
#define RAY_CAST_PARAMS_H
#include <SDL2/SDL.h>
typedef struct raycast_params{
    SDL_PixelFormat* format;
    struct world* w;
    Uint32* pixels;
    int width;
    int height;
    struct camera* cam;
    //point in the middle of each side of the screen
    float topDir[3];
    float rightDir[3];
    float botLeftCorner[3];
    
    //the rays that will be casted
    struct ray* rays;
} raycast_params;
#endif
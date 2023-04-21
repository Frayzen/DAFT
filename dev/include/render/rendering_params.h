#ifndef RENDERING_PARAMS_H
#define RENDERING_PARAMS_H
#include <SDL2/SDL.h>

typedef struct rendering_params{
    SDL_PixelFormat* format;
    struct world* w;
    Uint32* pixels;
    int width;
    int height;
    int screen_width;
    int screen_height;
    struct camera* cam;
    //pointers to the corners of the screen
    float topDir[3];
    float rightDir[3];
    float botLeftCorner[3];
    
    int shadow;
    int reflection;
} rendering_params;

rendering_params* init_rendering_params(struct world *w, int width, int height, struct camera* cam, float screen_scale, Uint32* pixels);

#endif

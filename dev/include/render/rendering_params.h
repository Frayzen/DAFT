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


typedef struct raycast_param{
    struct ray* r;
    struct world* w;
    //amout of reflection
    int reflection;
    //if the ray should compute shadow
    int shadow;
    //if the ray should return NULL or the background color if it doesn't hit anything
    int skybox;
    //the pixels that need to be computed for meshes
    int compute_meshes;
    //if the ray should consider the lights points as spheres
    int show_lights;
} raycast_param;

#endif

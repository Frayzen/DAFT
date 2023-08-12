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
    float3 topDir;
    float3 rightDir;
    float3 botLeftCorner;
    
    float FOV_x;
    float FOV_y;

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
    int compute_masks;
    //if the ray should consider the lights points as spheres
    int show_lights;
    //if the ray should consider the campoints as spheres
    int show_campoints;
} raycast_param;

#endif

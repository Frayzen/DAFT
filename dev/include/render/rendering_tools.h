#ifndef RENDERING_TOOLS_H
#define RENDERING_TOOLS_H
typedef struct raycast_params{
    SDL_PixelFormat* format;
    struct world* w;
    Uint32* pixels;
    int width;
    int height;
    camera* cam;
    //point in the middle of each side of the screen
    float leftSide[3];
    float rightSide[3];
    float topSide[3];
    float botSide[3];
    
    //the rays that will be casted
    struct ray* rays;
} raycast_params;

raycast_params* init_raycast_params(struct world *w, int width, int height, camera* cam);
void free_raycast_params(raycast_params* rcp);
#endif
#ifndef RENDERING_TOOLS_H
#define RENDERING_TOOLS_H
#include "../../include/render/rendering_tools.h"
#include "../../include/architecture/world.h"

raycast_params* init_raycast_params(world* wd, int width, int height, camera* cam, Uint32* pixels){
    raycast_params *rcp = malloc(sizeof(raycast_params));
    rcp->format = SDL_AllocFormat(SDL_PIXELFORMAT_RGBA8888);
    rcp->w = wd;
    rcp->width = width;
    rcp->height = height;
    rcp->cam = cam;
    rcp->pixels = pixels;
    return rcp;
}
void free_raycast_params(raycast_params* rcp){
    SDL_FreeFormat(rcp->format);
    free(rcp);
}
#endif

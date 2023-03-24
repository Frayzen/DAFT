#include "../../include/render/rendering_tools.h"

raycast_params* init_raycast_params(world* wd, int width, int height, camera* cam, Uint32* pixels){
    raycast_params *rcp = malloc(sizeof(raycast_params));
    rcp->format = SDL_AllocFormat(SDL_PIXELFORMAT_RGBA8888);
    rcp->w = wd;
    rcp->pixels = pixels;
    rcp->width = width;
    rcp->height = height;init_raycast_params
    rcp->cam = cam;
    return rcp;
}
void free_raycast_params(raycast_params* rcp){
    SDL_FreeFormat(rcp->format);
    free(rcp);
}
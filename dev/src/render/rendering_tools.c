#include "../../include/render/rendering_tools.h"

rendering_params* init_rendering_params(world* wd, int width, int height, camera* cam, float screen_scale, Uint32* pixels){
    rendering_params *rdp = malloc(sizeof(rendering_params));
    rdp->format = SDL_AllocFormat(SDL_PIXELFORMAT_RGBA8888);
    rdp->w = wd;
    rdp->width = width;
    rdp->height = height;
    rdp->cam = cam;
    rdp->pixels = pixels;
    rdp->shadow = 0;
    rdp->reflection = 0;
    rdp->screen_width = width*screen_scale;
    rdp->screen_height = height*screen_scale;
    return rdp;
}
void free_rendering_params(rendering_params* rdp){
    SDL_FreeFormat(rdp->format);
    free(rdp);
}

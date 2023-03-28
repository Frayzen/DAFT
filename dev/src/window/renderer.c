#include "../../include/window/renderer.h"

void render_screen(raycast_params* rcp)
{
    Uint32* pixels = rcp->pixels;
    int width = rcp->width;
    int height = rcp->height;
    SDL_PixelFormat* format = rcp->format;
    struct world* w = rcp->w;
    update_sides(rcp);
    #pragma omp parallel for
    for(int i = 0; i < width*height; i++){
        ray r = create_ray_interpolate(rcp, i%width, i/width);
        ray_cast(&r, w);
        if(r.last_hit != NULL){
            pixels[i] = SDL_MapRGBA(format, r.last_hit->color[0]*255, r.last_hit->color[1]*255, r.last_hit->color[2]*255, 255);
            free(r.last_hit);
        }
        else
            pixels[i] = SDL_MapRGBA(format, 0, 0, 0, 255);
    }
}
#include "../../include/window/renderer.h"

void render_screen(raycast_params* rcp)
{
    SDL_PixelFormat* format = rcp->format;
    struct world* w = rcp->w;
    Uint32* pixels = rcp->pixels;
    int width = rcp->width;
    int height = rcp->height;
    ray* rays = calloc(sizeof(ray), width*height);
    update_sides(rcp);
    rays[0].last_hit = calloc(sizeof(ray_result), 1);
    #pragma omp parallel for
    for(int i = 0; i < width*height; i++){
        ray r = create_ray_interpolate(rcp, i%width, i/width);
        ray_cast(&r, w);
        pixels[i] = SDL_MapRGBA(format, 255, 255, 255, 0);
    }
    free_sides(rcp);
    SDL_FreeFormat(format);
}
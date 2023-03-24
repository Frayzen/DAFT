#include "../../include/window/renderer.h"

void render_screen(Uint32* pixels, int width, int height, camera* cam, world* w)
{
    SDL_PixelFormat *format;
    format = SDL_AllocFormat(SDL_PIXELFORMAT_RGBA8888);
    ray* rays = init_rays(width, height, cam);
    rays[0].last_hit = calloc(sizeof(ray_hit), 1);
    #pragma omp parallel for
    for(int i = 0; i < width*height; i++){
        ray_cast(&rays[i], w);
        pixels[i] = SDL_MapRGBA(format, 255, 255, 255, 0);
    }
    free_rays(rays);
    SDL_FreeFormat(format);
}

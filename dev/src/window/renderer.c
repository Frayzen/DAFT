#include "../../include/window/renderer.h"

void render_screen(Uint32* pixels, int width, int height, camera* cam, world* w)
{
    SDL_PixelFormat *format;
    format = SDL_AllocFormat(SDL_PIXELFORMAT_RGBA8888);
    ray* rays = init_rays(width, height);
    #pragma omp parallel for
    for(int i = 0; i < width*height; i++){
        rays[i] = ray_cast_for_pixel(cam, w, i%width, i/width, width, height);
        float* color = rays[i].last_hit->color;
        pixels[i] = SDL_MapRGBA(format, 0, color[0]*255, color[1]*255, color[2]*255);
    }
    SDL_FreeFormat(format);
}

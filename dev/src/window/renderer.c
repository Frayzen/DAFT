#include "../../include/window/renderer.h"

void render(Uint32* pixels, int width, int height, camera* cam, world* w)
{
    SDL_PixelFormat *format;
    format = SDL_AllocFormat(SDL_PIXELFORMAT_RGBA8888);
    #pragma omp parallel for
    for(int i = 0; i < width*height; i++){
        pixels[i] = SDL_MapRGBA(format, 0, 0, 255, 255);
    }
    SDL_FreeFormat(format);
}

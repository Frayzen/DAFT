#include "../../include/window/renderer.h"

int percentage = 0;


void render_screen()
{
    //TODO: render the screen
}

void set_pixel(SDL_Surface *surface, int x, int y, Uint32 color)
{
    int bpp = surface->format->BytesPerPixel;
    Uint8 *p = (Uint8 *)surface->pixels + y * surface->pitch + x * bpp;

    if (bpp == 1)
        *p = color;
    else if (bpp == 2)
        *(Uint16 *)p = color;
    else if (bpp == 4)
        *(Uint32 *)p = color;
    else
    {
        if (SDL_BYTEORDER == SDL_BIG_ENDIAN)
        {
            p[0] = (color >> 16) & 0xff;
            p[1] = (color >> 8) & 0xff;
            p[2] = color & 0xff;
        }
        else
        {
            p[0] = color & 0xff;
            p[1] = (color >> 8) & 0xff;
            p[2] = (color >> 16) & 0xff;
        }
    }
}
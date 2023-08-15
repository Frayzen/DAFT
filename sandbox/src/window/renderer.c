#include "../../include/window/renderer.h"

int percentage = 0;

void renderScreen(DaftApp* app, SDL_Texture* texture)
{
    int i, j;
    int width = app->width;
    int height = app->height;
    int pitch;
    Uint32 *pixels;
    SDL_LockTexture(app->texture, NULL, (void **)&pixels, &pitch);
    //set the image transparent
    for (i = 0; i < height; i++)
    {
        for (j = 0; j < width; j++)
            pixels[i * width + j] = 0x00000000;
    }
    SDL_UnlockTexture(app->texture);
}
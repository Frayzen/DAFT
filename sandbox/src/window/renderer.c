#include "../../include/window/renderer.h"

int percentage = 0;

void renderScreen(DaftApp* app, SDL_Texture* texture)
{
    int i, j;
    int pitch;
    Uint32 *pixels;
    SDL_LockTexture(app->texture, NULL, (void **)&pixels, &pitch);
    int** raycastResults = malloc(sizeof(int*) * app->world->meshesCount);
    for (i = 0; i < app->world->meshesCount; i++)
    {
        raycastResults[i] = calloc(sizeof(int), SCREEN_HEIGHT * SCREEN_WIDTH);
    }
    for (int i = 0; i < app->world->meshesCount; i++)
    {
        Mesh *mesh = app->world->meshes[i];
        raycastMesh(app->camera, mesh, app->openCL, raycastResults[i]);
    }
    finishRaycasting(app->openCL);
    for(i = 0; i < SCREEN_WIDTH*SCREEN_HEIGHT; i++)
    {
        pixels[i] = 0x0000000;
        for (j = 0; j < app->world->meshesCount; j++)
        {
            //raycastResult starts at 1, so if it's not 0, it's a hit
            if(raycastResults[j][i] != 0)
            {
                pixels[i] = 0xFFFFFFFF;
                break;
            }
        }
    }
    for (i = 0; i < app->world->meshesCount; i++)
    {
        free(raycastResults[i]);
    }
    free(raycastResults);
    SDL_UnlockTexture(app->texture);
}
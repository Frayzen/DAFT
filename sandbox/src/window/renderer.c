#include "../../include/window/renderer.h"

int percentage = 0;

void renderScreen(DaftApp* app, SDL_Texture* texture)
{
    int i, j;
    int pitch;
    unsigned int *pixels;
    SDL_LockTexture(app->texture, NULL, (void **)&pixels, &pitch);
    for (int i = 0; i < app->world->meshesCount; i++)
    {
        rasterizeBbox(app->world->meshes[i], app->camera, pixels);
        Mesh *mesh = app->world->meshes[i];
        raycastMesh(app->camera, mesh, app->openCL, pixels);
    }
    finishRaycasting(app->openCL);
    SDL_UnlockTexture(app->texture);
}
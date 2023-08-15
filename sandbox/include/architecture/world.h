#ifndef WORLD_H
#define WORLD_H

#include "camera.h"
#include "mesh.h"
#include <SDL2/SDL.h>

typedef struct{
    Camera* cam;
    Mesh* mesh;
    SDL_Surface* skybox;
} World;
#endif
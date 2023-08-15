#ifndef WORLD_H
#define WORLD_H

#include "camera.h"
#include "mesh.h"
#include "../constants.h"
#include <SDL2/SDL.h>

typedef struct{
    Camera* camera;
    int meshesCount;
    Mesh** meshes;
    SDL_Surface* skybox;
} World;

World* createWorld();
void freeWorld(World* world);
void worldAddMesh(World* world, Mesh* msh);
#endif
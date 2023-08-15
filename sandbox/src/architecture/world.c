#include "../../include/architecture/world.h"

World* createWorld(){
    World* wd = calloc(sizeof(World), 1);
    return wd;
}

void freeWorld(World* world){
    if(world->skybox != NULL){
        SDL_FreeSurface(world->skybox);
    }
    for (int i = 0; i < world->meshesCount; i++)
    {
        freeMesh(world->meshes[i]);
    }
    free(world->meshes);
    free(world);
}

void worldAddMesh(World* world, Mesh* msh){
    world->meshesCount++;
    world->meshes = realloc(world->meshes, sizeof(Mesh*) * world->meshesCount);
    world->meshes[world->meshesCount - 1] = msh;
}
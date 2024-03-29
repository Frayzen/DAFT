#ifndef WORLD_H
#define WORLD_H
#include "camera.h"
#include "light.h"
#include "mesh.h"
#include <stdlib.h>
#include "ray.h"
#include "campoint.h"
typedef struct world
{
    int size_cameras;
    int size_lights;
    int size_meshes;
    int size_spheres;
    int size_campoints;
    camera** cameras;
    light** lights;
    mesh** meshes;
    sphere* spheres;
    //skybox texture, NULL if no skybox
    SDL_Surface* skybox;
    campoint * campoints;

}world;


void add_camera(world* wd, camera* cam);
void add_light(world* wd, light* lt);
void add_mesh(world* wd, mesh* msh);
void add_sphere(world* wd, sphere* s);
void add_campoint(world* wd, campoint* cp);

world* init_world();
void free_world(world* wd);

#endif

#include "camera.h"
#include "light.h"
#include "mesh.h"
#include <stdlib.h>
#include "ray.h"
#pragma once
typedef struct world
{

    int size_cameras;
    int size_lights;
    int size_meshes;
    camera** cameras;
    light** lights;
    mesh** meshes;

}world;


void add_camera(world* wd, camera* cam);
void add_light(world* wd, light* lt);
void add_mesh(world* wd, mesh* msh);

world* init_world();
void free_world(world* wd);
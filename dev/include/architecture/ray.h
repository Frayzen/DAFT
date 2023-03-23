#include "triangle.h"
#include "mesh.h"
#include <stdlib.h>

#pragma once
typedef struct ray_hit
{
    float mint;
    triangle* tri;
    mesh* m;
    float color[3];
} ray_hit;
typedef struct ray
{
	float pos[3];
	float dir[3];

    float mint;
    float maxt;

    //last mesh is the mesh that the ray was in last
    ray_hit* last_hit;
    //current mesh is the mesh that the ray is currently in
    mesh* current_mesh;
}ray;


ray* create_rays(int width, int height);
void free_rays(ray* rays);
void ray_hit(ray* r, triangle* tri, float new_mint, float color[3]);
#include "triangle.h"
#include "camera.h"
#include "mesh.h"
#include <stdlib.h>
#include "../utils/daft_math.h"
#include <omp.h>

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


ray* init_rays(int width, int height, camera* cam);
void free_rays(ray* rays);
void ray_hit_triangle(ray* r, triangle* tri, float new_mint, float color[3]);
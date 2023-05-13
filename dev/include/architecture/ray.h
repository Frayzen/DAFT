#ifndef RAY_H
#define RAY_H
#include "../render/rendering_params.h"
#include "triangle.h"
#include "camera.h"
#include "mesh.h"
#include <stdlib.h>
#include "../utils/daft_math.h"
#include <omp.h>
#include "./material.h"

typedef struct ray_result
{

    float mint;
    triangle* tri;
    mesh* m;
    float normal[3];
    float pos[3];
    material* mat;
    float color[3];
} ray_result;
typedef struct ray
{
    
	float pos[3];
    //direction of the ray
	float dir[3];
    //last mesh is the mesh that the ray was in last
    ray_result* last_hit;
    //current mesh is the mesh that the ray is currently in
    mesh* current_mesh;
}ray;

void update_cam_sides(rendering_params* rdp);
ray create_ray_interpolate(rendering_params* rdp, int x_pix, int y_pix);
void ray_update_result(ray* r, triangle* tri, float new_mint, float normal[3], material* mat, float color[3]);
#endif
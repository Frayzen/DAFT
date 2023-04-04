#include "triangle.h"
#include "camera.h"
#include "mesh.h"
#include <stdlib.h>
#include "../utils/daft_math.h"
#include "../render/ray_cast_params.h"
#include <omp.h>

#ifndef RAY_H
#define RAY_H
typedef struct ray_result
{

    float mint;
    triangle* tri;
    mesh* m;
    float normal[3];
    float color[3];
    float reflectivity;

} ray_result;
typedef struct ray
{
    
	float pos[3];
	float dir[3];
    //last mesh is the mesh that the ray was in last
    ray_result* last_hit;
    //current mesh is the mesh that the ray is currently in
    mesh* current_mesh;
}ray;

void update_sides(raycast_params* rdo);
ray create_ray_interpolate(raycast_params* rcp, int x_pix, int y_pix);
void ray_update_result(ray* r, triangle* tri, float new_mint, float color[3], float normal[3], float reflectivity);
#endif
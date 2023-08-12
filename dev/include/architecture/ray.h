#ifndef RAY_H
#define RAY_H
#include "../render/rendering_params.h"
#include "camera.h"
#include "mesh.h"
#include <stdlib.h>
#include "../utils/daft_math.h"
#include <omp.h>
#include "./material.h"

typedef struct ray_result
{
    float mint;
    int tri;
    mesh *m;
    float3 normal;
    float3 pos;
    material *mat;
    float3 color;
    float3 uvw;
} ray_result;

typedef struct ray
{
    float3 pos;
    // direction of the ray
    float3 dir;
    // last mesh is the mesh that the ray was in last
    ray_result *last_hit;
    // current mesh is the mesh that the ray is currently in
    mesh *current_mesh;
} ray;

void update_cam_sides(rendering_params *rdp);
ray create_ray_interpolate(rendering_params *rdp, int x_pix, int y_pix);
void ray_update_result(ray *r, int tri, float new_mint, float3 normal, material *mat, float3 color, float3 uvw);
#endif
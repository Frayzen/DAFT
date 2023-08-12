#ifndef MESH_H
#define MESH_H
#include <stdlib.h>
#include "vectors.h"
#include "../render/rendering_params.h"
#include "./camera.h"
#include "../utils/daft_math.h"
#include "sphere.h"
#include "./material.h"

 typedef struct mesh{
    int vs_size;
    float3* vs;
    int vt_size;
    float2* vt;
    int vn_size;
    float3* vn;
    
    int tri_size;
    int3 *tri_v;
    int3 *tri_t;
    int3 *tri_n;

    int bboxes_size;
    float3* b_min;
    float3* b_max;
    //negative for triangles, positive for bboxes, 0 for empty
    int *b_children;

    int mat_size;
    material* mats;
}mesh;

void free_mesh(mesh* msh);
#endif
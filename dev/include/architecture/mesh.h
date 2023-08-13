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
    int3 *tri_v; //vertex index
    int3 *tri_t; //texture index
    int3 *tri_n; //normal index
    int* tri_m; //material index

    int bboxes_size;
    float3* b_min;
    float3* b_max;
    //negative for triangles, positive for bboxes, 0 for empty
    int *b_children;

    int mat_size;
    material* mats;
}mesh;


void get_vt_from_tri(mesh* m, int tri, float2 vt[3]);
void get_vn_from_tri(mesh* m, int tri, float3 vn[3]);
void get_v_from_tri(mesh* m, int tri, float3 v[3]);
void free_mesh(mesh* msh);
#endif
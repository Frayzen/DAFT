#include <stdlib.h>
#include "triangle.h"
#include "bbox.h"
#include "../render/ray_cast_params.h"
#include "./camera.h"
#include "../utils/daft_math.h"
#include "sphere.h"
#ifndef MESH_H
#define MESH_H

 typedef struct mesh{
    int nb_vertices;
    int nb_triangles;
    float** vertices;
    int tri_last_level;
    int depth;
    int no_extra;
    bbox* box;
    float reflectivity;
}mesh;

void free_mesh(mesh* msh);
void get_vertex_from_triangle(mesh* m, triangle* tri, float* v1, float* v2, float* v3);
#endif
#include <stdlib.h>
#include "triangle.h"
#include "bbox.h"

#pragma once

 typedef struct mesh{
    int nb_vertices;
    int nb_triangles;
    float** vertices;
    int tri_last_level;
    int depth;
    int no_extra;
    triangle* triangles;
    bbox* box;
}mesh;

void free_mesh(mesh* msh);
void get_vertex_from_triangle(mesh* m, triangle* tri, float* v1, float* v2, float* v3);

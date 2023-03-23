#include <stdlib.h>
#include "triangle.h"
#include "bbox.h"
#pragma once

 typedef struct mesh{
    int nb_vertices;
    int nb_triangles;
    float* vertices[3];
    triangle* triangles;
    bbox* box;
}mesh;

float * get_middle(triangle * t, mesh *m);
float * get_max_points(mesh *m);
float * get_min_points(mesh *m);
void free_mesh(mesh* msh);
void get_vertex_from_triangle(mesh* m, triangle* tri, float* v1, float* v2, float* v3);

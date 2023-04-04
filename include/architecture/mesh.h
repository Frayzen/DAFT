#include <stddef.h>
#pragma once
#include "triangle.h"

 typedef struct mesh{
    int nb_vertices;
    int nb_triangles;
    float* vertices[3];
    triangle* triangles;
}mesh;

float * get_middle(triangle t, mesh *m);
float * get_max_points(mesh *m);
float * get_min_points(mesh *m);
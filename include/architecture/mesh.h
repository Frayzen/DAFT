#include <stddef.h>
#pragma once

typedef struct mesh{
    int nb_vertices;
    int nb_triangles;
    float* vertices[3];
    triangle* triangles;
};


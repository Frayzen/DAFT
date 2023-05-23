#ifndef MESH_H
#define MESH_H
#include <stdlib.h>
#include "triangle.h"
#include "bbox.h"
#include "../render/rendering_params.h"
#include "./camera.h"
#include "../utils/daft_math.h"
#include "sphere.h"
#include "./material.h"

 typedef struct mesh{
    int nb_vertices;
    float** vertices;
    
    int nb_texture_vertices;
    float** texture_vertices;


    int nb_normal_vertices;
    float** normal_vertices;
    
    int nb_triangles;
    int tri_last_level;
    int depth;
    int no_extra;
    bbox* box;
    material* mats;
    int nb_mat;
}mesh;

void free_mesh(mesh* msh);
void get_vertex_from_triangle(mesh* m, triangle* tri, float* v1, float* v2, float* v3);
#endif
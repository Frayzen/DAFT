#include "mesh.h"
#include "bbox.h"
#include "../constants.h"

#pragma once


typedef struct kdtree {
    int axis;
    float value;
    int nb_triangles;
    triangle *triangles;
    struct kdtree *left;
    struct kdtree *right;
    bbox *box;

} kdtree;


kdtree * kdtree_create(triangle *triangles, int nb_triangles, int depth, mesh * m);
triangle * sort_triangles(triangle * tris, int nb_tris, int axis, mesh * m);
kdtree * init_kdtree(mesh * m);
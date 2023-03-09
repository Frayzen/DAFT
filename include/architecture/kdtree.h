#include "../architecture/kdtree.h"
#include "../architecture/mesh.h"
#include "bbox.h"
#inclue "constants.h"

#pragma once


typedef struct kdtree {
    int axis;
    float value;
    int nb_triangles;
    triangle *triangles;
    kdtree *left;
    kdtree *right;
    bbox *box;

} kdtree;


kdtree * kdtree_create(triangle *triangles, int nb_triangles, int depth, mesh * m);
triangle * sort_triangles(triangle * tris, int nb_tris, int axis, mesh * m);
kdtree * init_kdtree(mesh * m);
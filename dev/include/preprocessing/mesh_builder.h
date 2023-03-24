#include "../architecture/world.h"
#ifndef MESH_BUILDER_H
#define MESH_BUILDER_H
void add_vertex(mesh * m, float p[3]);
void add_tri(mesh* m, int v1, int v2, int v3);
mesh * build_mesh(int no_vert, int no_tri, int id);
#endif
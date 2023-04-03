#include "../architecture/world.h"
#ifndef MESH_BUILDER_H
#define MESH_BUILDER_H
void add_vertex(mesh * m, float p[3]);
void add_tri(mesh* m, int points[3]);
mesh * build_mesh(int no_vert, int no_tri);
#endif
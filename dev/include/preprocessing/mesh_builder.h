#include "../architecture/world.h"
#ifndef MESH_BUILDER_H
#define MESH_BUILDER_H
void add_v(mesh * m, float p[3]);
void add_vt(mesh * m, int vt[2]);
void add_vn(mesh * m, float vt[3]);
void add_tri(mesh* m, int v[3], int vt[3], int vn[3]);
mesh * build_mesh(int no_vert, int no_trim, int text_vert);
#endif
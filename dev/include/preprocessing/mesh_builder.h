#include "../architecture/world.h"
#pragma once
void add_vertex(mesh * m, float p[3]);
void add_tri(mesh* m, int v1, int v2, int v3);
mesh * build_mesh(int no_vert, int no_tri, int id);
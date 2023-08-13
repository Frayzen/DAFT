#include "../architecture/world.h"
#include <assert.h>
#ifndef MESH_BUILDER_H
#define MESH_BUILDER_H
void add_v(mesh * m, float3 p);
void add_vt(mesh * m, float2 vt);
void add_vn(mesh * m, float3 vt);
void add_tri(mesh* m, int3 v, int3 vt, int3 vn, int material);
mesh * init_mesh(int no_vert, int no_trim, int text_vert, int norm_text);
void build_mesh(mesh* m);
#endif

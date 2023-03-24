#include "../../include/preprocessing/obj_builder.h"


void add_tri(mesh * m, size_t a, size_t b, size_t c)
{
    triangle* t = init_triangle(a, b, c);
    add_tri_to_bbox(m, m->bounding_box, m->depth, t);
}

void add_vertex(mesh * m, float x, float y, float z)
{
	m->vertexes[m->v_size] = npoint(x,y,z);
	m->v_size++;
}

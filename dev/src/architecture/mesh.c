#include "../../include/architecture/mesh.h"


mesh * init_mesh(size_t no_vert, size_t no_tri, size_t id)
{

    mesh * m = (mesh *)malloc(sizeof(mesh));
    m->depth = compute_depth(no_tri-1);
    m->tri_last_level = compute_tri_last_level(m->depth, no_tri);
    m->no_extra = compute_no_extra(no_tri, m->tri_last_level, m->depth);
    m->bounding_box = build_bbox(m->depth, m->tri_last_level, m->no_extra);
	m->id_m = id;
	m->v_size = 0;
	m->vertexes = malloc(sizeof(point)*no_vert);

	return m;
}
void free_mesh(mesh* msh){
    free(msh->vertices);
    free(msh->triangles);
    free(msh);
}
void get_vertex_from_triangle(mesh* m, triangle* tri, float* v1, float* v2, float* v3){
    for(int i = 0; i < 3; i++){
        v1[i] = m->vertices[tri->vert[0]][i];
        v2[i] = m->vertices[tri->vert[1]][i];
        v3[i] = m->vertices[tri->vert[2]][i];
    }
}
#include "../../include/architecture/mesh.h"

void free_mesh(mesh* msh){
    free_bbox(msh->box);
    for(int i = 0; i < msh->nb_vertices; i++)
        free(msh->vertices[i]);

    for(int i = 0; i < msh->nb_normal_vertices; i++)
        free(msh->normal_vertices[i]);
    for(int i = 0; i < msh->nb_texture_vertices; i++)
        free(msh->texture_vertices[i]);
    free(msh->normal_vertices);
    free(msh->texture_vertices);
    free(msh->vertices);
    free_mat(msh->mat);
    free(msh);
}
void get_vertex_from_triangle(mesh* m, triangle* tri, float* v1, float* v2, float* v3){
    copy(m->vertices[tri->v[0]], v1);
    copy(m->vertices[tri->v[1]], v2);
    copy(m->vertices[tri->v[2]], v3);
}
#include "../../include/architecture/mesh.h"

void free_mesh(mesh* msh){
    free_bbox(msh->box);
    for(int i = 0; i < msh->nb_vertices; i++)
        free(msh->vertices[i]);
    free(msh->vertices);
    free(msh);
}
void get_vertex_from_triangle(mesh* m, triangle* tri, float* v1, float* v2, float* v3){
    for(int i = 0; i < 3; i++){
        v1[i] = m->vertices[tri->vert[0]][i];
        v2[i] = m->vertices[tri->vert[1]][i];
        v3[i] = m->vertices[tri->vert[2]][i];
    }
}
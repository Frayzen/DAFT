#include "../../include/architecture/mesh.h"

void free_mesh(mesh* msh){
    free_bbox(msh->box);
    for(int i = 0; i < msh->nb_vertices; i++)
        free(msh->vertices[i]);
    free(msh->vertices);
    free(msh);
}
void get_vertex_from_triangle(mesh* m, triangle* tri, float* v1, float* v2, float* v3){
    copy(m->vertices[tri->vert[0]], v1);
    copy(m->vertices[tri->vert[1]], v2);
    copy(m->vertices[tri->vert[2]], v3);
}
void load_texture(mesh* m, char* path){
    SDL_Surface* surface = IMG_Load(path);
    if(surface == NULL){
        printf("Could not load the texture '%s'\n", path);
        return;
    }
    m->texture = SDL_ConvertSurfaceFormat(surface, SDL_PIXELFORMAT_RGBA8888, 0);
    SDL_FreeSurface(surface);
    printf("Texture '%s' loaded successfully !\n", path);
}
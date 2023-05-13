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
    free(msh->mat);
    if(msh->texture != NULL)
        SDL_FreeSurface(msh->texture);
    free(msh);
}
void get_vertex_from_triangle(mesh* m, triangle* tri, float* v1, float* v2, float* v3){
    copy(m->vertices[tri->v[0]], v1);
    copy(m->vertices[tri->v[1]], v2);
    copy(m->vertices[tri->v[2]], v3);
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
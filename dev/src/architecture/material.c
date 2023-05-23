#include "../../include/architecture/material.h"

//shininess more than 1
//reflection less than 1
material* mat_init(float ambient[3], float diffuse[3], float specular[3], float shininess, float reflection){
    material* mat = malloc(sizeof(material));
    copy(ambient, mat->ambient);
    copy(diffuse, mat->diffuse);
    copy(specular, mat->specular);
    mat->shininess = shininess;
    mat->reflection = reflection;
    mat->ambientText = NULL;
    mat->diffuseText = NULL;
    mat->specularText = NULL;
    return mat;
}

material* create_mat_from_color(){
    return mat_init((float[]){0.1,0.1,0.1}, (float[]){.8,.8,.8}, (float[]){1,1,1}, .2, 0);
}

material* def_mat(float shininess, float reflection){
    return mat_init((float[]){0.4,0.4,0.4}, (float[]){1,1,1}, (float[]){.8,.8,.8}, shininess, reflection);
}
material* default_mat(){
    return def_mat(50,0);
}

void load_texture(SDL_Surface** texture, char* path){
    SDL_Surface* surface = IMG_Load(path);
    if(surface == NULL){
        printf("Could not load the texture '%s'\n", path);
        return;
    }
    *texture = SDL_ConvertSurfaceFormat(surface, SDL_PIXELFORMAT_RGBA8888, 0);
    SDL_FreeSurface(surface);
    printf("Texture '%s' loaded successfully !\n", path);
}
void free_mat(material* m){
    if(m->ambientText != NULL)
        SDL_FreeSurface(m->ambientText);
    if(m->diffuseText != NULL)
        SDL_FreeSurface(m->diffuseText);
    if(m->specularText != NULL)
        SDL_FreeSurface(m->specularText);
    free(m);
}

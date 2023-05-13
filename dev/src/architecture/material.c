#include "../../include/architecture/material.h"

//shininess more than 1
//reflection less than 1
material* mat_init(float r, float g, float b, float ambient[3], float diffuse[3], float specular[3], float shininess, float reflection){
    material* mat = malloc(sizeof(material));
    mat->color[0] = r;
    mat->color[1] = g;
    mat->color[2] = b;
    copy(ambient, mat->ambient);
    copy(diffuse, mat->diffuse);
    copy(specular, mat->specular);
    mat->shininess = shininess;
    mat->reflection = reflection;
    return mat;
}

material* create_mat_from_color(float r, float g, float b){
    return mat_init(r, g, b, (float[]){0.1,0.1,0.1}, (float[]){.8,.8,.8}, (float[]){1,1,1}, .2, 0);
}

material* def_mat(float r, float g, float b, float shininess, float reflection){
    return mat_init(r, g, b, (float[]){0.1,0.1,0.1}, (float[]){1,1,1}, (float[]){.5,.5,.5}, shininess, reflection);
}
material* default_mat(){
    return def_mat(1,1,1,50,0);
}
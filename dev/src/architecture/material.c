#include "../../include/architecture/material.h"

material* mat_init(float r, float g, float b, illumination ambient, illumination diffuse, illumination specular, float shininess, float reflection){
    material* mat = malloc(sizeof(material));
    mat->color[0] = r;
    mat->color[1] = g;
    mat->color[2] = b;
    mat->ambient = ambient;
    mat->diffuse = diffuse;
    mat->specular = specular;
    mat->shininess = shininess;
    mat->reflection = reflection;
    return mat;
}
material* create_mat_from_color(float r, float g, float b){
    return mat_init(r, g, b, def_illum(), def_illum(), def_illum(), .2, 0);
}

illumination def_illum(){
    return illum(1,1,1,100);
}
//shininess more than 1
//reflection less than 1
material* def_mat(float r, float g, float b, float shininess, float reflection){
    return mat_init(r, g, b, illum(1,1,1,2), illum(1,1,1,1), def_illum(1,1,1,1), shininess, reflection);
}
material* default_mat(){
    return def_mat(1,1,1,50,0);
}

void free_material(material* mat){
    free(mat);
}
//intensity is more than 1 (1 means no intensity)
illumination illum(float r, float g, float b, float intensity){
    illumination i;
    i.color[0] = max(0,min(1,r));
    i.color[1] = max(0,min(1,g));
    i.color[2] = max(0,min(1,b));
    //normalize(i.color, i.color);
    i.intensity = 1-(1/intensity);
    return i;
}
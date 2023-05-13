#include "../../include/architecture/sphere.h"

sphere* sphere_init(float x, float y, float z, float radius, material* mat){
    sphere* s = malloc(sizeof(sphere));
    s->mat = mat;
    s->pos[0] = x;
    s->pos[1] = y;
    s->pos[2] = z;
    s->radius = radius;
    return s;
}
void free_sphere(sphere* s){
    free(s->mat);
    free(s);
}
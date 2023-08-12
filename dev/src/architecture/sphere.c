#include "../../include/architecture/sphere.h"

sphere* sphere_init(float3 pos, float radius, material* mat){
    sphere* s = malloc(sizeof(sphere));
    s->mat = mat;
    copy(pos, s->pos);
    s->radius = radius;
    return s;
}
void free_sphere(sphere* s){
    free(s->mat);
    free(s);
}
#include "../../include/architecture/sphere.h"

sphere* sphere_init(float x, float y, float z, float radius, float r, float g, float b, float reflectivity){
    sphere* s = malloc(sizeof(sphere));
    s->reflectivity = reflectivity;
    s->pos[0] = x;
    s->pos[1] = y;
    s->pos[2] = z;
    s->radius = radius;
    s->color[0] = r;
    s->color[1] = g;
    s->color[2] = b;
    return s;
}
void free_sphere(sphere* s){
    free(s);
}
#include "../../include/architecture/sphere.h"

sphere* sphere_init(float x, float y, float z, float radius, float r, float g, float b){
    sphere* s = malloc(sizeof(sphere));
    s->pos[0] = x;
    s->pos[1] = y;
    s->pos[2] = z;
    s->radius = radius;
    s->color[0] = r;
    s->color[1] = g;
    s->color[2] = b;
    return s;
}
#ifndef SPHERE_H
#define SPHERE_H
#include <stdlib.h>
#include "./material.h"

typedef struct sphere
{
    float pos[3];
    float radius;
    material* mat;
} sphere;

sphere* sphere_init(float x, float y, float z, float r, material* mat);
void free_sphere(sphere* s);
#endif
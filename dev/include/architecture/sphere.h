#ifndef SPHERE_H
#define SPHERE_H
#include <stdlib.h>
#include "./material.h"
#include "../architecture/vectors.h"

typedef struct sphere
{
    float3 pos;
    float radius;
    material* mat;
} sphere;

sphere* sphere_init(float3 pos, float r, material* mat);
void free_sphere(sphere* s);
#endif
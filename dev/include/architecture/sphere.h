#include <stdlib.h>
#ifndef SPHERE_H
#define SPHERE_H

typedef struct sphere
{
    float pos[3];
    float color[3];
    float radius;
} sphere;

sphere* sphere_init(float x, float y, float z, float r, float r2, float g, float b);

#endif
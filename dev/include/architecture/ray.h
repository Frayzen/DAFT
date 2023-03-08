#include "triangle.h"
#include "mesh.h"
#include <stdlib.h>

#pragma once
typedef struct ray
{
    int computed;
	float pos[3];
	float dir[3];
	int hit;
    float mint;
    float color[3];
	triangle *tri;
    mesh* m;
}ray;

ray* create_rays(int width, int height);
void free_rays(ray* rays);
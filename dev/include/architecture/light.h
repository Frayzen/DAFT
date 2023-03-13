#include <stdlib.h>

#pragma once
typedef struct light
{
	float pos[3];
    float color[3];
	float intensity;
}light;

//init
light* init_light(float pos[3], float color[3], float intensity);
//free
void free_light(light* lt);
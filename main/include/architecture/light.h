#ifndef LIGHT_H
#define LIGHT_H
#include <stdlib.h>
#include "../utils/daft_math.h"
#include "./material.h"
#include "./sphere.h"
typedef struct light
{
	float color[3];
	float pos[3];
	sphere* s;
}light;

//init
light* init_light(float pos[3], float color[3]);
void free_light(light* lt);
#endif
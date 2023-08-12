#ifndef LIGHT_H
#define LIGHT_H
#include <stdlib.h>
#include "../architecture/vectors.h"
#include "../utils/daft_math.h"
#include "./material.h"
#include "./sphere.h"
typedef struct light
{
	float3 color;
	float3 pos;
	sphere* s;
}light;

//init
light* init_light(float3 pos, float3 color);
void free_light(light* lt);
#endif
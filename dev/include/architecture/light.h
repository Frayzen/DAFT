#ifndef LIGHT_H
#define LIGHT_H
#include <stdlib.h>
#include "../utils/daft_math.h"
#include "./material.h"
typedef struct light
{
	illumination illum;
	float pos[3];
}light;

//init
light* init_light(float pos[3], illumination illum);
#endif
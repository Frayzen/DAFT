#include <stdlib.h>

#ifndef LIGHT_H
#define LIGHT_H
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
#endif
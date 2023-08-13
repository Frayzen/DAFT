#ifndef CAMPPOINT_H
#define CAMPPOINT_H
#include "sphere.h"
#include <assert.h>

typedef struct campoint{
    struct sphere *s;
    float time;
    float yaw;
    float pitch;
} campoint;


campoint* init_campoint(float3 pos, float yaw, float pitch);
#endif
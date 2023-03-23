#include <stdlib.h>
#pragma once

//LBBOX  is the max number of children in a bounding box
#define LBBOX 4
typedef struct bbox
{//either children or tris is null
    point min;
    point max;
    size_t total;
    size_t maxtotal;
    struct bbox ** children;
    triangle * tris;
    //also maxtotal
    size_t c_size;
}bbox;

bbox * init_bbox(float min[3], float max[3]);
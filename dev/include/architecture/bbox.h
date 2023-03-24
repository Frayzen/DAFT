#include <stdlib.h>
#include "triangle.h"
#pragma once

//LBBOX  is the max number of children in a bounding box
#define LBBOX 4
typedef struct bbox
{//either children or tris is null
    float min[3];
    float max[3];
    size_t total;
    size_t maxtotal;
    struct bbox ** children;
    triangle * tris;
    //also maxtotal
    size_t c_size;
}bbox;
void free_bbox(bbox *b);
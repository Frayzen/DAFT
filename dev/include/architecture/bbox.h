#include <stdlib.h>
#include "triangle.h"
#ifndef BBOX_H
#define BBOX_H

//LBBOX  is the max number of children in a bounding box
#define LBBOX 4
typedef struct bbox
{//either children or tris is null
    float min[3];
    float max[3];
    //total number of triangles in the bbox (including children)
    int total;
    //max number of triangles in the bbox (including children)
    int maxtotal;
    struct bbox ** children;
    triangle * tris;
    //number of children (either bbox or tris) in the bbox
    int c_size;
}bbox;
void free_bbox(bbox *b);

#endif
#include <stdlib.h>
#pragma once

typedef struct bbox{
    float min[3];
    float max[3];
}bbox;

bbox * init_bbox(float min[3], float max[3]);
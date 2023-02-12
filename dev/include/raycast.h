#include <math.h>
#include "utils.h"
#include "architecture.h"
#pragma once

typedef struct raycast_param{
    camera* cam;
    world* wd;
    size_t x_pix;
    size_t y_pix;
    size_t width;
    size_t height;
} raycast_param;



int ray_cast_pixel(raycast_param params);

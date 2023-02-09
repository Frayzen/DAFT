#include <math.h>
#include "utils.h"
#include "architecture.h"

#pragma once

typedef struct raycast_param{
    camera* cam;
    size_t x_pix;
    size_t y_pix;
} raycast_param;



int ray_cast_pixel(raycast_param params);

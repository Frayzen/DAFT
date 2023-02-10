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
    int r;
    int g;
    int b;
} raycast_param;


typedef struct color{
    Uint8 r;
    Uint8 g;
    Uint8 b;
} color;

color ray_cast_pixel(raycast_param params);

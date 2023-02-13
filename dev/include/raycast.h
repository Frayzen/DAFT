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



ray ray_cast_pixel(raycast_param params);
ray nray(camera* cam, size_t x, size_t y, size_t w, size_t h);
void ray_intersect(triangle * tri, mesh * m, ray * r);

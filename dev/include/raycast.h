#include <math.h>
#include "utils.h"
#include "architecture.h"
#pragma once


ray ray_cast_pixel(camera* cam, world* wd, size_t x, size_t y, size_t w, size_t h);
void ray_intersect(triangle * tri, mesh * m, ray * r);
ray ray_cast_neighbour(camera* cam, world* wd, size_t x, size_t y, size_t w, size_t h, ray rays[]);

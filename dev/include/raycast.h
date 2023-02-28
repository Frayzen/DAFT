#include <math.h>
#include "utils.h"
#include "architecture.h"
#pragma once


ray ray_cast_pixel(camera* cam, world* wd, size_t x, size_t y, size_t w, size_t h);
void ray_intersect(triangle * tri, mesh * m, ray * r);
int cast_neighbour(ray *src, ray tgt);
ray get_ray(size_t width, size_t height, size_t x_pix, size_t y_pix, camera* cam);
void ray_cast_neighbour(world* wd, camera* cam, size_t x, size_t y, size_t w, size_t h, ray rays[], size_t target_id);

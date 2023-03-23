#include "../architecture/ray.h"
#include "../architecture/camera.h"
#include "../architecture/world.h"
#include "../utils/daft_math.h"
#include "./mesh_renderer.h"

#pragma once
ray ray_cast_for_pixel(camera* cam, world* wd, size_t x, size_t y, size_t w, size_t h);
void ray_cast(ray* r, world* w);
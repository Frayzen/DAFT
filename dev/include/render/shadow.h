#include "../architecture/ray.h"
#include "../architecture/camera.h"
#include "../architecture/world.h"
#include "../utils/daft_math.h"
#include "mesh_renderer.h"
#include "render.h"
#ifndef SHADOW_H
#define SHADOW_H

int shadow_hit(ray* shadow_ray, light* l, float prevt);

void shadow_render(ray* ray, world* w, int real_time);

#endif

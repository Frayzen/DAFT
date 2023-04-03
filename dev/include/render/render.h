#include "../architecture/ray.h"
#include "../architecture/camera.h"
#include "../architecture/world.h"
#include "../utils/daft_math.h"
#include "./mesh_renderer.h"
#include "./sphere_renderer.h"

#ifndef RENDER_H
#define RENDER_H
void ray_cast(ray* r, world* w, camera* cam, int shadow);
#endif
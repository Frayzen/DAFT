#ifndef RENDER_H
#define RENDER_H
#include "../architecture/ray.h"
#include "../architecture/camera.h"
#include "../architecture/world.h"
#include "../utils/daft_math.h"
#include "./mesh_renderer.h"
#include "./sphere_renderer.h"
#include "../physic/shadow.h"
#include "../physic/reflection.h"

void ray_cast(raycast_param* rcp);
#endif
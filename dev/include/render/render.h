#include "../architecture/ray.h"
#include "../architecture/camera.h"
#include "../architecture/world.h"
#include "../utils/daft_math.h"
#include "./mesh_renderer.h"
#include "./sphere_renderer.h"
#include "../physic/shadow.h"
#include "../physic/reflection.h"

#ifndef RENDER_H
#define RENDER_H
void ray_cast(ray* r, world* w, int reflection, int shadow);
void basic_ray_cast(ray* r, world* w);
void ray_cast_reflection(ray* r, world* w, int nb_reflections);
#endif
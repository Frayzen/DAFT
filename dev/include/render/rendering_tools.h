#ifndef RENDERING_TOOLS_H
#define RENDERING_TOOLS_H
#include "../architecture/world.h"
#include "ray_cast_params.h"

struct raycast_params* init_raycast_params(struct world *w, int width, int height, camera* cam, float screen_scale, Uint32* pixels);
void free_raycast_params(raycast_params* rcp);
#endif
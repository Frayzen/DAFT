#ifndef RENDERING_TOOLS_H
#define RENDERING_TOOLS_H
#include "./ray_cast_params.h"
#include "../architecture/world.h"
raycast_params* init_raycast_params(struct world *w, int width, int height, camera* cam);
void free_raycast_params(raycast_params* rcp);
#endif
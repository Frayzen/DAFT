#ifndef RENDERING_TOOLS_H
#define RENDERING_TOOLS_H
#include "../architecture/world.h"
#include "../../include/render/rendering_params.h"

rendering_params* init_rendering_params(world *w, int width, int height, camera* cam, float screen_scale, Uint32* pixels);
void free_rendering_params(rendering_params* rdp);
#endif
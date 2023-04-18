#ifndef BBOX_RASTERIZER_H
#define BBOX_RASTERIZER_H

#include "../architecture/world.h"
#include "../render/ray_cast_params.h"
#include "../utils/daft_math.h"

void render_rasterize_bbox(raycast_params* rcp, int* pixels);

#endif
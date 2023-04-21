#ifndef BBOX_RASTERIZER_H
#define BBOX_RASTERIZER_H

#include "../architecture/world.h"
#include "../render/rendering_params.h"
#include "../utils/daft_math.h"

void render_rasterize_bbox(rendering_params* rdp, int* pixels);

#endif
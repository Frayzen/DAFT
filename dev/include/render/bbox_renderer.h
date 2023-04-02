#include "../architecture/bbox.h"
#include "../architecture/ray.h"
#include "./triangle_render.h"
#include <math.h>
#ifndef BBOX_RENDERER_H
#define BBOX_RENDERER_H

int bbox_render(bbox * b, ray * r);
#endif
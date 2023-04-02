#include "../architecture/bbox.h"
#include "../architecture/ray.h"
#include "./triangle_render.h"
#include <math.h>
#ifndef BBOX_RENDERER_H
#define BBOX_RENDERER_H
#define QUALITY_WIDTH 1920
#define QUALITY_HEIGHT 1920

int bbox_render(bbox * b, ray * r);
#endif
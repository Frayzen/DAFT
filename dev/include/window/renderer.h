#include "../architecture/world.h"
#include "../render/rendering_tools.h"
#include "../render/render.h"
#include "../constants.h"
#include "../render/bbox_rasterizer.h"
#include <omp.h>
#include <SDL2/SDL.h>
#include <pthread.h>

#ifndef WINDOW_RENDERER_H
#define WINDOW_RENDERER_H
void render_screen(rendering_params* rdp);
void render_quality(rendering_params* rdp);
#endif
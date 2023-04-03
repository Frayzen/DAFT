#include "../architecture/world.h"
#include "../render/rendering_tools.h"
#include "../render/render.h"
#include <omp.h>
#include <SDL2/SDL.h>
#include <pthread.h>

#ifndef WINDOW_RENDERER_H
#define WINDOW_RENDERER_H

#define QUALITY_WIDTH 1000
#define QUALITY_HEIGHT 1000

void render_screen(raycast_params* rcp);
void render_quality(raycast_params* rcp);
#endif
#include "../architecture/world.h"
#include "../render/rendering_tools.h"
#include "../render/render.h"
#include <omp.h>
#include <SDL2/SDL.h>

#ifndef WINDOW_RENDERER_H
#define WINDOW_RENDERER_H

void render_screen(raycast_params* rcp);
#endif
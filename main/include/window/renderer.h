#include "../architecture/world.h"
#include "../render/rendering_tools.h"
#include "../render/render.h"
#include "../constants.h"
#include "../render/rasterizer.h"
#include <omp.h>
#include <stdio.h>
#include <SDL2/SDL.h>

#ifndef WINDOW_RENDERER_H
#define WINDOW_RENDERER_H
void render_screen(rendering_params* rdp);
void render_quality_image(rendering_params* rdp);
void render_quality_video(rendering_params* rdp);
#endif
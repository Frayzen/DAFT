#ifndef WINDOW_RENDERER_H
#define WINDOW_RENDERER_H
#include "../architecture/world.h"
#include "../constants.h"
#include <omp.h>
#include <stdio.h>
#include <string.h>
#include <SDL2/SDL.h>
#include "../window/window.h"
#include "../acceleration/opencl.h"
void renderScreen(DaftApp* app, SDL_Texture* texture);
#endif
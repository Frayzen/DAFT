#include "../architecture/world.h"
#include "../constants.h"
#include <omp.h>
#include <stdio.h>
#include <SDL2/SDL.h>
#include "../window/window.h"

#ifndef WINDOW_RENDERER_H
#define WINDOW_RENDERER_H
void renderScreen(DaftApp* app, SDL_Texture* texture);
#endif
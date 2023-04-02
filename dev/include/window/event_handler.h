#include <SDL2/SDL.h>
#include "./window.h"
#include "../architecture/camera.h"
#include <stdio.h>

#ifndef EVENT_HANDLER_H
#define EVENT_HANDLER_H

void handle_events(SDL_Event event, int* quit, app_params* params);

#endif
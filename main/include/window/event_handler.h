#include <SDL2/SDL.h>
#include "./window.h"
#include "../architecture/camera.h"
#include <stdio.h>
#include "../architecture/world.h"

#ifndef EVENT_HANDLER_H
#define EVENT_HANDLER_H

#define MOVING_SPEED 0.01
void handle_events(int* quit, app_params* params);

#endif
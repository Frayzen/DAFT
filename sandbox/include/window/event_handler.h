#ifndef EVENT_HANDLER_H
#define EVENT_HANDLER_H

#include <SDL2/SDL.h>
#include "./window.h"
#include <stdio.h>
#include <math.h>
#include "../constants.h"

void handle_events(int* quit, app_params* params);

#endif
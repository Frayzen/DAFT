#include <stdio.h>
#include <omp.h>
#include <pthread.h>
#include <stdlib.h>
#include <time.h>
#include <err.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "architecture.h"

#pragma once
struct app_params{
    size_t width;
    size_t height;
    size_t FPS_UPPER_LIMIT;
    SDL_Window* window;
    SDL_Renderer* renderer;
    world* wd;
    camera* cam;
} typedef app_params;

int setup_window(app_params* params);
int render_camera(app_params* params);

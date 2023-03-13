#include <stdio.h>
#include <omp.h>
#include <pthread.h>
#include <stdlib.h>
#include <time.h>
#include <err.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "../architecture/world.h"
#include "../architecture/camera.h"
#include "renderer.h"
#include "../constants.h"
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
int launch_screen(app_params* params);
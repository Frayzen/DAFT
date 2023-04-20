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
#include "../render/rendering_tools.h"
#ifndef WINDOW_H
#define WINDOW_H
struct app_params{
    int width;
    int height;
    int render_scale;
    int FPS_UPPER_LIMIT;
    SDL_Window* window;
    SDL_Renderer* renderer;
    SDL_Texture *texture;
    world* wd;
    camera* cam;
    raycast_params* rcp;
} typedef app_params;

int setup_window(app_params* params);
int launch_screen(app_params* params);
void free_window(app_params* params);
#endif
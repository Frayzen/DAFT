#ifndef WINDOW_H
#define WINDOW_H

#include <stdio.h>
#include <omp.h>
#ifdef _WIN32
#include <windows.h>
#endif
#include <stdlib.h>
#include <time.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "../architecture/camera.h"
#include "../architecture/world.h"
#include "../architecture/camera.h"

struct app_params{
    int width;
    int height;
    float screen_scale;
    int FPS_UPPER_LIMIT;
    SDL_Window* window;
    SDL_Renderer* renderer;
    SDL_Texture *texture;
    World* wd;
    Camera* cam;
} typedef app_params;

int setup_window(app_params* params);
int launch_screen(app_params* params);
void free_window(app_params* params);
#endif
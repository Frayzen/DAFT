#ifndef WINDOW_H
#define WINDOW_H

#ifdef _WIN32
#endif
#include <stdio.h>
#include <stdlib.h>
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

#include "event_handler.h"
#include "skybox.h"
#include "renderer.h"
#include "time.h"

int setup_window(app_params* params);
int launch_screen(app_params* params);
void free_window(app_params* params);
#endif
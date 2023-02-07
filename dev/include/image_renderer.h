#pragma once
#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include <time.h>
#include <err.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
struct thread_info{
    //xstart 
    size_t xs;
    //xend
    size_t xe;
    //ystart
    size_t ys;
    //yend
    size_t ye;

    SDL_Surface* surface;
} typedef thread_info;

struct app_params{
    size_t width;
    size_t height;
    size_t FPS_UPPER_LIMIT;
    SDL_Window* window;
    SDL_Renderer* renderer;
} typedef app_params;

void render(SDL_Renderer* renderer, size_t width, size_t height);
int setup_renderer(app_params* params);
int launch(app_params* params);

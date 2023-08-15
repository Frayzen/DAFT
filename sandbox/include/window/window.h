#ifndef WINDOW_H
#define WINDOW_H
#include <stdio.h>
#include <stdlib.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "../architecture/camera.h"
#include "../architecture/world.h"
#include "../architecture/camera.h"
#include "../acceleration/opencl.h"

struct DaftApp{
    SDL_Window* window;
    SDL_Renderer* renderer;
    SDL_Texture *texture;
    World* world;
    Camera* camera;
    DaftOpenCL* openCL;
} typedef DaftApp;

#include "event_handler.h"
#include "skybox.h"
#include "renderer.h"
#include "time.h"

DaftApp* initApp();
void launchScreen(DaftApp* app);
void freeApp(DaftApp* app);
#endif
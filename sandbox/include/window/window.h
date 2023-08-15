#ifndef WINDOW_H
#define WINDOW_H
#include <stdio.h>
#include <stdlib.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "../architecture/camera.h"
#include "../architecture/world.h"
#include "../architecture/camera.h"

struct DaftApp{
    int width;
    int height;
    SDL_Window* window;
    SDL_Renderer* renderer;
    SDL_Texture *texture;
    World* world;
    Camera* camera;
} typedef DaftApp;

#include "event_handler.h"
#include "skybox.h"
#include "renderer.h"
#include "time.h"

DaftApp* initApp();
void launchScreen(DaftApp* app);
void freeApp(DaftApp* app);
#endif
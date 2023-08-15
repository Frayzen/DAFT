#ifndef SKYBOX_H
#define SKYBOX_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "../constants.h"
#include "../architecture/world.h"
#include "../architecture/camera.h"
#include "window.h"
#include <math.h>
void defineSkyPoints(DaftApp* app, SDL_Texture* skybox_texture);
void worldSetSkybox(World* world, char* path);
#endif
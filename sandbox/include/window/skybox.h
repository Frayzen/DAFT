#ifndef SKYBOX_H
#define SKYBOX_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "../constants.h"
#include "../architecture/world.h"
#include "../architecture/camera.h"

//normalized dir
void define_sky_points(SDL_Renderer* renderer, SDL_Texture* skybox_texture, World* wd);
void load_skybox(World* wd, char* path);
#endif
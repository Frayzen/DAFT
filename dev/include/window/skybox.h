#ifndef SKYBOX_H
#define SKYBOX_H

#include <SDL2/SDL.h>
#include "../utils/daft_math.h"
#include "../render/ray_cast_params.h"
#include "../architecture/camera.h"
#include "../architecture/world.h"

//normalized dir
void define_sky_points(SDL_Rect* first_src, SDL_Rect* second_src, SDL_Rect* first_to, SDL_Rect* second_to, raycast_params* rcp);
#endif
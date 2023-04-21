#ifndef SKYBOX_H
#define SKYBOX_H

#include <SDL2/SDL.h>
#include "../utils/daft_math.h"
#include "../render/rendering_params.h"
#include "../architecture/camera.h"
#include "../architecture/world.h"

//normalized dir
void define_sky_points(SDL_Renderer* renderer, SDL_Texture* skybox_texture, rendering_params* rdp);
#endif
#ifndef MATERIAL_H
#define MATERIAL_H

#include <stdlib.h>
#include "../constants.h"
#include "../utils/daft_math.h"
#include <SDL2/SDL_image.h>
#include <SDL2/SDL.h>
typedef struct {
    float color[3];
    float ambient[3];
    float diffuse[3];
    float specular[3];
    float shininess;
    float reflection;
    SDL_Surface* texture;
} material;

material* create_mat_from_color(float r, float g, float b);
material* mat_init(float r, float g, float b, float ambient[3], float diffuse[3], float specular[3], float shininess, float reflection);

material* default_mat();
material* def_mat(float r, float g, float b, float shininess, float reflection);

void load_texture(material* m, char* path);
void free_mat(material* m);
#endif
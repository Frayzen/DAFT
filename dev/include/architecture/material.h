#ifndef MATERIAL_H
#define MATERIAL_H

#include <stdlib.h>
#include <stdio.h>
#include "../constants.h"
#include "../utils/daft_math.h"
#include "../architecture/vectors.h"
#include <SDL2/SDL_image.h>
#include <SDL2/SDL.h>
typedef struct {
    float3 ambient;
    float3 diffuse;
    float3 specular;
    float shininess;
    float reflection;
    char name[256];
    SDL_Surface* ambientText;
    SDL_Surface* diffuseText;
    SDL_Surface* specularText;
} material;

material* create_mat_from_color(float r, float g, float b);
material* mat_init(float3 ambient, float3 diffuse, float3 specular, float shininess, float reflection);

material* default_mat();
material* def_mat(float shininess, float reflection);

void load_texture(SDL_Surface** texture, char* path);
void free_mat(material* m);
#endif

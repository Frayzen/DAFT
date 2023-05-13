#ifndef MATERIAL_H
#define MATERIAL_H

#include <stdlib.h>
#include "../constants.h"
#include "../utils/daft_math.h"

typedef struct illumination{
    float color[3];
    float intensity;
} illumination;

typedef struct {
    float color[3];
    illumination ambient;
    illumination diffuse;
    illumination specular;
    float shininess;
    float reflection;
} material;

material* create_mat_from_color(float r, float g, float b);
material* mat_init(float r, float g, float b, illumination ambient, illumination diffuse, illumination specular, float shininess, float reflection);
void free_material(material* mat);

illumination illum(float r, float g, float b, float intensity);
illumination def_illum();
material* default_mat();
material* def_mat(float r, float g, float b, float shininess, float reflection);
#endif
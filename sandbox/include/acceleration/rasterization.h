#ifndef RASTERIZATION_H
#define RASTERIZATION_H

#include "../architecture/mesh.h"
#include "../architecture/camera.h"
#include "../architecture/vectors.h"
#include <string.h>

void rasterizeBbox(Mesh* m, Camera* cam, int* result);

#endif
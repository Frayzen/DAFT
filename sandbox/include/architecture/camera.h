#ifndef CAMERA_H
#define CAMERA_H

#include "vectors.h"
#include <stdlib.h>

typedef struct {
    Vector3 position;
    Vector3 rotation;
    Vector2 FOV;
    Vector3 movement_speed;
    Vector2 rotation_speed;
    Vector3* rays;
} Camera;

#include "../constants.h"
#include <math.h>
#include <stdio.h>

Camera* createCamera();

#endif
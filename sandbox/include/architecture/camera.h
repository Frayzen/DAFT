#ifndef CAMERA_H
#define CAMERA_H

#include "vectors.h"

typedef struct {
    Vector3 pos;
    Vector2 angles;
    Vector2 FOV;
    Vector3 movement_speed;
    Vector2 rotation_speed;
} Camera;

#endif
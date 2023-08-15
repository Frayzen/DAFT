#ifndef CAMERA_H
#define CAMERA_H

#include "vectors.h"
#include <stdlib.h>

typedef struct {
    Vector3 pos;
    Vector2 angles;
    Vector2 FOV;
    Vector3 movement_speed;
    Vector2 rotation_speed;
} Camera;

Camera* createCamera(Vector3 pos, Vector2 angles, Vector2 FOV);

#endif
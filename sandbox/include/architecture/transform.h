#ifndef TRANSFORM_H
#define TRANSFORM_H

#include "vectors.h"

typedef struct{
    Vector3 position;
    Vector3 rotation;
    Vector3 scale;
} Transform;

Transform createTransformPRS(Vector3 position, Vector3 rotation, Vector3 scale);
Transform createTransformPR(Vector3 position, Vector3 rotation);
Transform createTransformPS(Vector3 position, Vector3 scale);
Transform createTransformP(Vector3 position);
Transform createTransformS(Vector3 scale);
Transform createTransformR(Vector3 rotation);
Transform createTransform();
Vector3 transformVector3(Vector3 v, Transform* t);
#endif
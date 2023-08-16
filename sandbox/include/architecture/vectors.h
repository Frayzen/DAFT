#ifndef VECTORS_H
#define VECTORS_H

typedef struct {
    float x;
    float y;
    float z;
} Vector3;

typedef struct {
    float x;
    float y;
} Vector2;

typedef struct {
    int x;
    int y;
    int z;
} int3;

#include <math.h>

Vector2 normalize2(Vector2 v);
Vector3 normalize(Vector3 v);
Vector3 add(Vector3 v1, Vector3 v2);
Vector3 sub(Vector3 v1, Vector3 v2);
Vector3 scale(Vector3 v, float s);
Vector3 rotate(Vector3 v, Vector3 rotation);
Vector3 rotateRPY(Vector3 v, Vector3 rotation);

#endif
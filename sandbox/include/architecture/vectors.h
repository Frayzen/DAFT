#ifndef VECTORS_H
#define VECTORS_H

typedef struct {
    float x;
    float y;
    float z;
} Vector3;

typedef struct {
    float c1[3];
    float c2[3];
    float c3[3];
} Matrix;

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
Vector3 scalef(Vector3 v, float s);
Vector3 scale(Vector3 v, Vector3 s);
Vector3 rotate(Vector3 v, Vector3 rotation);
Vector3 rotateRPY(Vector3 v, Vector3 rotation);
Matrix createRotationMatrix(Vector3 rotation);
Vector3 multiplyMatrixVector(Matrix m, Vector3 v);
#endif
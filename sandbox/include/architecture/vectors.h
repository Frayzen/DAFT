#ifndef VECTORS_H
#define VECTORS_H

typedef struct {
    float x;
    float y;
    float z;
} Vector3;

typedef struct {
    float r1[3];
    float r2[3];
    float r3[3];
} Matrix3;

typedef struct {
    float r1[4];
    float r2[4];
    float r3[4];
    float r4[4];
} Matrix4;

typedef struct {
    float r1[4];
    float r2[3];
    float r3[2];
    float r4[1];
} SymmetricMatrix4;


typedef struct {
    float x;
    float y;
} Vector2;

typedef struct {
    float x;
    float y;
    float z;
    float w;
} Vector4;

typedef struct {
    int x;
    int y;
    int z;
} int3;

typedef struct {
    int x;
    int y;
} int2;

#include <math.h>

#define VECTOR_FORWARD (Vector3){1, 0, 0}
#define VECTOR_UP (Vector3){0, 1, 0}
#define VECTOR_RIGHT (Vector3){0, 0, 1}

#ifndef max
    #define max(a,b) ((a) > (b) ? (a) : (b))
#endif
#ifndef min
    #define min(a,b) ((a) < (b) ? (a) : (b))
#endif

float dist(Vector3 v1, Vector3 v2);
Vector2 normalize2(Vector2 v);
Vector3 normalize(Vector3 v);
Vector3 add(Vector3 v1, Vector3 v2);
Vector3 sub(Vector3 v1, Vector3 v2);
Vector3 scalef(Vector3 v, float s);
Vector3 scale(Vector3 v, Vector3 s);
Vector3 rotate(Vector3 v, Vector3 rotation);
Vector3 rotateRPY(Vector3 v, Vector3 rotation);
Matrix3 createRotationMatrix(Vector3 rotation);
Vector3 multiplyMatrixVector3(Matrix3 m, Vector3 v);
Vector4 multiplyMatrixVector4(Matrix4 m, Vector4 v);
Vector4 multiplyMatrixVectTranspose4(Matrix4 m, Vector4 v);
Vector3 minv3(Vector3 v1, Vector3 v2);
Vector3 maxv3(Vector3 v1, Vector3 v2);
Vector3 midPoint(Vector3 v1, Vector3 v2);
float dot(Vector3 v1, Vector3 v2);
float dot4(Vector4 v1, Vector4 v2);
Vector3 cross(Vector3 v1, Vector3 v2);
int inverseMat4(Matrix4* m, Matrix4* r);
#endif
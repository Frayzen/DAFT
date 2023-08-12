#include <math.h>
#include "../constants.h"
#include "../architecture/vectors.h"

#ifndef DAFT_MATH_H
#define DAFT_MATH_H
#define copy(a, r) r.x = a.x; r.y = a.y; r.z = a.z;
#define define(a, x, y, z) a.x = x; a.y = y; a.z = z;
#define copy2(a, r) r.x = a.x; r.y = a.y;
#define define2(a, x, y) a.x = x; a.y = y;
#define crossProduct(a, b, r) r.x = a.y * b.z - a.z * b.y; r.y = a.z * b.x - a.x * b.z; r.z = a.x * b.y - a.y * b.x
#define dotProduct(a, b) a.x * b.x + a.y * b.y + a.z * b.z
#define add(a, b, r) r.x = a.x + b.x; r.y = a.y + b.y; r.z = a.z + b.z
#define minus(a, b, r) r.x = a.x - b.x; r.y = a.y - b.y; r.z = a.z - b.z
#define scale(a, b, r) r.x = a.x * b; r.y = a.y * b; r.z = a.z * b;
#define scale_vector(a, b, r) r.x = a.x * b.x; r.y = a.y * b.y; r.z = a.z * b.z;
#define normSquared(a) a.x * a.x + a.y * a.y + a.z * a.z
#define norm(a) sqrt(a.x * a.x + a.y * a.y + a.z * a.z)
#define projectOn(a, b) (dotProduct(a, b)) / (norm(b))
#ifndef min
#define min(a, b) (a < b ? a : b)
#endif
#ifndef max
#define max(a, b) (a > b ? a : b)
#endif

float3 normalize(float3 p);
float distance(float3 a, float3 b);
float project(float3 a, float3 b);
float3 project_onto(float3 a, float3 b);
float3 reflect(float3 v, float3 n);
#endif
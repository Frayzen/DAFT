#include <math.h>
#include "../constants.h"

#ifndef DAFT_MATH_H
#define DAFT_MATH_H
#define copy(a, r) r[0] = a[0]; r[1] = a[1]; r[2] = a[2]
#define crossProduct(a, b, r) r[0] = a[1] * b[2] - a[2] * b[1]; r[1] = a[2] * b[0] - a[0] * b[2]; r[2] = a[0] * b[1] - a[1] * b[0]
#define dotProduct(a, b) a[0] * b[0] + a[1] * b[1] + a[2] * b[2]
#define add(a, b, r) r[0] = a[0] + b[0]; r[1] = a[1] + b[1]; r[2] = a[2] + b[2]
#define minus(a, b, r) r[0] = a[0] - b[0]; r[1] = a[1] - b[1]; r[2] = a[2] - b[2]
#define scale(a, b, r) r[0] = a[0] * b; r[1] = a[1] * b; r[2] = a[2] * b;
#define normSquared(a) a[0] * a[0] + a[1] * a[1] + a[2] * a[2]
#define norm(a) sqrt(a[0] * a[0] + a[1] * a[1] + a[2] * a[2])
#define projectOn(a, b) (dotProduct(a, b)) / (norm(b))
#define min(a, b) (a < b ? a : b)
#define max(a, b) (a > b ? a : b)

void normalize(float* p, float* r);
float distance(float* a, float* b);
float project(float* a, float* b);
void project_onto(float* a, float* b, float* r);
#endif
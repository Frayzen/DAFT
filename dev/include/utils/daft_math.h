#include <math.h>
#include "../constants.h"

#ifndef DAFT_MATH_H
#define DAFT_MATH_H
#define copy(a, r) r[0] = a[0]; r[1] = a[1]; r[2] = a[2];
#define crossProduct(a, b, r) r[0] = a[1] * b[2] - a[2] * b[1]; r[1] = a[2] * b[0] - a[0] * b[2]; r[2] = a[0] * b[1] - a[1] * b[0];
#define dotProduct(a, b) a[0] * b[0] + a[1] * b[1] + a[2] * b[2];
#define add(a, b, r) r[0] = a[0] + b[0]; r[1] = a[1] + b[1]; r[2] = a[2] + b[2];
#define minus(a, b, r) r[0] = a[0] - b[0]; r[1] = a[1] - b[1]; r[2] = a[2] - b[2];
#define scale(a, b, r) r[0] = a[0] * b; r[1] = a[1] * b; r[2] = a[2] * b;
#define normSquared(a) a[0] * a[0] + a[1] * a[1] + a[2] * a[2];
#define norm(a) sqrt(a[0] * a[0] + a[1] * a[1] + a[2] * a[2]);
#define distance(a,b)sqrt(pow(b[0]-a[0],2)+ pow(b[1]-a[1],2)+pow(b[2]-a[2],2))
#define projectOn(a, b, r) scale(b, dotProduct(a, b) / dotProduct(b, b), r);

void normalize(float* p, float* r);
#endif
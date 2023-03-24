#include <math.h>
#include "../constants.h"

#pragma once
#define copy(a, r) r[0] = a[0]; r[1] = a[1]; r[2] = a[2];
#define crossProduct(a, b, r) r[0] = a[1] * b[2] - a[2] * b[1]; r[1] = a[2] * b[0] - a[0] * b[2]; r[2] = a[0] * b[1] - a[1] * b[0];
#define dotProduct(a, b) a[0] * b[0] + a[1] * b[1] + a[2] * b[2];
#define add(a, b, r) r[0] = a[0] + b[0]; r[1] = a[1] + b[1]; r[2] = a[2] + b[2];
#define minus(a, b, r) r[0] = a[0] - b[0]; r[1] = a[1] - b[1]; r[2] = a[2] - b[2];
#define scale(a, b, r) r[0] = a[0] * b; r[1] = a[1] * b; r[2] = a[2] * b;

void normalize(float* p, float* r);
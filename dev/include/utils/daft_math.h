#include <math.h>
#include "../constants.h"

#pragma once
void copy(float a[3], float* r);
void crossProduct(float a[3], float b[3], float* r);
float dotProduct(float a[3], float b[3]);
void normalize(float a[3], float* r);
void add(float a[3], float b[3], float* r);
void minus(float a[3], float b[3], float* r);
void scale(float a[3], float b, float* r);
#include "../../include/utils/daft_math.h"

void copy(float a[3], float* r) {
    r[0] = a[0];
    r[1] = a[1];
    r[2] = a[2];
}

void crossProduct(float a[3], float b[3], float* r) {
    r[0] = a[1] * b[2] - a[2] * b[1];
    r[1] = a[2] * b[0] - a[0] * b[2];
    r[2] = a[0] * b[1] - a[1] * b[0];
}

float dotProduct(float a[3], float b[3]) {
    return a[0] * b[0] + a[1] * b[1] + a[2] * b[2];
}

void normalize(float a[3], float* r) {
    float norm = sqrtf(dotProduct(a, a));
    r[0] = a[0] / norm;
    r[1] = a[1] / norm;
    r[2] = a[2] / norm;
}

void add(float a[3], float b[3], float* r) {
    r[0] = a[0] + b[0];
    r[1] = a[1] + b[1];
    r[2] = a[2] + b[2];
}
void minus(float a[3], float b[3], float* r) {
    r[0] = a[0] - b[0];
    r[1] = a[1] - b[1];
    r[2] = a[2] - b[2];
}
void scale(float a[3], float b, float* r) {
    r[0] = a[0] * b;
    r[1] = a[1] * b;
    r[2] = a[2] * b;
}

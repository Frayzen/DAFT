#pragma once

float[3] crossProduct(float[3] a, float[3] b) {
    return float[3] {
        a[1] * b[2] - a[2] * b[1],
        a[2] * b[0] - a[0] * b[2],
        a[0] * b[1] - a[1] * b[0]
    };
}

float dotProduct(float[3] a, float[3] b) {
    return a[0] * b[0] + a[1] * b[1] + a[2] * b[2];
}

float[3] normalize(float[3] a) {
    float length = sqrt(dotProduct(a, a));
    return float[3] {
        a[0] / length,
        a[1] / length,
        a[2] / length
    };
}
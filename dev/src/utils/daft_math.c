#include "../../include/utils/daft_math.h"

void normalize(float* p, float* r)
{
    float sum = sqrt(p[0] * p[0] + p[1] * p[1] + p[2] * p[2]);
    if(sum == 0)
    {
        r[0] = p[0];
        r[1] = p[1];
        r[2] = p[2];
        return;
    }
    r[0] = p[0] / sum;
    r[1] = p[1] / sum;
    r[2] = p[2] / sum;
}

float distance(float* a, float* b){
    float3 diff;
    minus(a, b, diff);
    return norm(diff);
}

float project(float* w, float* v){
    float wv = dotProduct(w, v);
    float nsqr = normSquared(v);
    return wv / nsqr;
}

void reflect(float* v, float* n, float* r){
    float3 proj;
    scale(n, 2 * dotProduct(v, n), proj);
    minus(proj, v, r);
}
#include "../../include/utils/daft_math.h"

void normalize(float3 p, float3 r)
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

float distance(float3 a, float3 b){
    float3 diff;
    minus(a, b, diff);
    return norm(diff);
}

float project(float3 w, float3 v){
    float wv = dotProduct(w, v);
    float nsqr = normSquared(v);
    return wv / nsqr;
}

void reflect(float3 v, float3 n, float3* r){
    float3 proj;
    scale(n, 2 * dotProduct(v, n), proj);
    minus(proj, v, (*r));
}
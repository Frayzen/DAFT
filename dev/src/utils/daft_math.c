#include "../../include/utils/daft_math.h"

float3 normalize(float3 p)
{
    float3 r;
    float sum = norm(p);
    if(sum == 0)
    {
        copy(p, r);
        return r;
    }
    scale(p, 1 / sum, r);
    return r;
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

float3  reflect(float3 v, float3 n){
    float3 proj;
    scale(n, 2 * dotProduct(v, n), proj);
    float3 r;
    minus(proj, v, r);
    return r;
}
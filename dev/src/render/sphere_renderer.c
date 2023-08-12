#include "../../include/render/sphere_renderer.h"

int sphere_render(sphere * s, ray * r){
    float3 diff, onSphere, normal, dir;
    normalize(r->dir, dir);
    float a = 1;
    minus(r->pos, s->pos, diff);
    float b = dotProduct(diff, dir);
    b*=2;
    float c = normSquared(diff) - s->radius*s->radius;
    float discriminant = b*b - 4*a*c;
    if(discriminant < 0)
        return 0;
    float sqrtDisc = sqrt(discriminant);
    float t = -b - sqrtDisc;
    if(t < 0)
        t = -b + sqrtDisc;
    t/=(2*a);
    if(t < 0)
        return 0;
    if(r->last_hit && r->last_hit->mint < t) //previous was closer
        return 0;
    scale(dir, t, onSphere);
    add(r->pos, onSphere, onSphere);
    minus(onSphere, s->pos, normal);
    normalize(normal, normal);
    ray_update_result(r, NULL, t, normal, s->mat, (float[]){1,1,1}, NULL);
    return 1;
}
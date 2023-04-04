#include "../../include/render/sphere_renderer.h"

int sphere_render(sphere * s, ray * r){
    float dir[3], hyp[3], onSphere[3], normal[3];
    double angle, side, xsqr, t;
    
    copy(r->dir, dir);
    minus(s->pos, r->pos, hyp);
    float dphp = dotProduct(hyp, dir);
    float nd = norm(dir);
    float nh = norm(hyp);
    angle = (acos(dphp/(nh*nd)))*180/M_PI;
    if (angle > 90) {return 0;}
    side = dotProduct(hyp, dir);
    side/=nd;
    
    float nshyp = normSquared(hyp);
    if (s->radius*s->radius <= nshyp - side*side)
        return 0;
    xsqr = s->radius*s->radius - nshyp + side*side;
    //on sphere
    t = side - sqrt(xsqr);
    normalize(r->dir, dir);
    scale(dir, t, onSphere);
    add(r->pos, onSphere, onSphere);

    //normal
    minus(onSphere, s->pos, normal);
    float val = dotProduct(normal, r->dir);

    if(val < 0)
        val*=-1;
    if(val > 1)
        val = 1;
    float color[3];
    scale(s->color, val, color);
    ray_update_result(r, NULL, t, color, normal);
    return 1;
}
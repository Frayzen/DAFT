#include "../../include/render/bbox_renderer.h"

float min(float x, float y){
    return x < y ? x : y;
}
float max(float x, float y){
    return x > y ? x : y;
}

int intersect_bbox(bbox* b, ray* r){
    float tmin = -INFINITY;
    float tmax = INFINITY;
    float x = r->dir[0];
    if(x != 0){
        float ox = r->pos[0];
        float tx1 = (b->min[0] - ox)/x;
        float tx2 = (b->max[0] - ox)/x;
        tmin = max(tmin, min(tx1, tx2));
        tmax = min(tmax, max(tx1, tx2));
    }
    if(tmax < tmin)
        return 0;
    float y = r->dir[1];
    if(y != 0){
        float oy = r->pos[1];
        float ty1 = (b->min[1] - oy)/y;
        float ty2 = (b->max[1] - oy)/y;
        tmin = max(tmin, min(ty1, ty2));
        tmax = min(tmax, max(ty1, ty2));
    }
    if(tmax < tmin)
        return 0;
    float z = r->dir[2];
    if(z != 0){
        float oz = r->pos[2];
        float tz1 = (b->min[2] - oz)/z;
        float tz2 = (b->max[2] - oz)/z;
        tmin = max(tmin, min(tz1, tz2));
        tmax = min(tmax, max(tz1, tz2));
    }
    return tmax >= tmin;
}

int bbox_render(bbox* b, ray* r){
    int intersect = intersect_bbox(b, r);
    if(intersect){
        if(b->tris){
            for(int i = 0; i < b->c_size; i++)
                triangle_render(&b->tris[i], r);
        }else{
            for(int i = 0; i < b->c_size; i++)
                bbox_render(b->children[i], r);
        }
        return r->last_hit != NULL;
    }
    return 0;
}
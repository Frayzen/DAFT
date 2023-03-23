#include "../../include/render/bbox_renderer.h"

int intersect_bbox(bbox* b, ray* r){
    float tmin = -INFINITY;
    float tmax = INFINITY;
    float x = r->dir.x;
    if(x != 0){
        float ox = r->pos.x;
        float tx1 = (b->min.x - ox)/x;
        float tx2 = (b->max.x - ox)/x;
        tmin = max(tmin, min(tx1, tx2));
        tmax = min(tmax, max(tx1, tx2));
    }
    float y = r->dir.y;
    if(y != 0){
        float oy = r->pos.y;
        float ty1 = (b->min.y - oy)/y;
        float ty2 = (b->max.y - oy)/y;
        tmin = max(tmin, min(ty1, ty2));
        tmax = min(tmax, max(ty1, ty2));
    }
    float z = r->dir.z;
    if(z != 0){
        float oz = r->pos.z;
        float tz1 = (b->min.z - oz)/z;
        float tz2 = (b->max.z - oz)/z;
        tmin = max(tmin, min(tz1, tz2));
        tmax = min(tmax, max(tz1, tz2));
    }
    return tmax >= tmin;
}

int bbox_render(bbox* b, ray* r){
    if(intersect_bbox(r, b)){
        if(b->tris){
            for(size_t i = 0; i < b->c_size; i++)
                triangle_render(&b->tris[i], r);
        }else{
            for(size_t i = 0; i < b->c_size; i++)
                bbox_render(r, b->children[i]);
        }
        return r->last_hit;
    }
    return 0;
}
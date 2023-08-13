#include "../../include/render/bbox_renderer.h"

int intersect_bbox(int bbox, ray* r){
    mesh* m = r->current_mesh;
    float tmin = -INFINITY;
    float tmax = INFINITY;
    float x = r->dir.x;
    float3 min = m->b_min[bbox];
    float3 max = m->b_max[bbox];
    if(x != 0){
        float ox = r->pos.x;
        float tx1 = (min.x - ox)/x;
        float tx2 = (max.x - ox)/x;
        tmin = max(tmin, min(tx1, tx2));
        tmax = min(tmax, max(tx1, tx2));
    }
    if(tmax < tmin)
        return 0;
    float y = r->dir.y;
    if(y != 0){
        float oy = r->pos.y;
        float ty1 = (min.y - oy)/y;
        float ty2 = (max.y - oy)/y;
        tmin = max(tmin, min(ty1, ty2));
        tmax = min(tmax, max(ty1, ty2));
    }
    if(tmax < tmin)
        return 0;
    float z = r->dir.z;
    if(z != 0){
        float oz = r->pos.z;
        float tz1 = (min.z - oz)/z;
        float tz2 = (max.z - oz)/z;
        tmin = max(tmin, min(tz1, tz2));
        tmax = min(tmax, max(tz1, tz2));
    }
    return tmax >= tmin;
}

int bbox_render(int bbox, ray* r){
    mesh* m = r->current_mesh;
    int intersect = intersect_bbox(bbox, r);
    if(intersect){
        for (size_t i = 0; i < LBBOX; i++)
        {
            int id = m->b_children[bbox*LBBOX+i];
            if(id < 0){
                //triangle
                triangle_render(-id, r);
            }else{
                //bbox
                bbox_render(id, r);
            }
        }
        return r->last_hit != NULL;
    }
    return 0;
}
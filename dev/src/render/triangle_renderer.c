#include "../../include/render/triangle_renderer.h"

int triangle_render(triangle* tri, ray* r){
    mesh* m = r->current_mesh;
    float EPSILON = 0.0000001;
    float3 v0, v1, v2;
    get_vertex_from_triangle(m, tri, v0, v1, v2);
    float3 edge1, edge2, h, s, q;
    minus(v1, v0, edge1);
    minus(v2, v0, edge2);
    crossProduct(r->dir, edge2, h);
    float a = dotProduct(edge1, h);
    if (a > -EPSILON && a < EPSILON){
        return 0;    // This ray is parallel to this triangle.
    }
    float f = 1.0 / a;
    minus(r->pos, v0, s);
    float u = dotProduct(s, h);
    u*=f;
    if (u < 0.0 || u > 1.0){
        return 0;
    }
    crossProduct(s, edge1, q);
    float v = dotProduct(r->dir, q);
    v*=f;
    if (v < 0 || u+v > 1){
        return 0;
    }
    float t = dotProduct(edge2, q);
    t*=f;
    if(t > EPSILON){
        if(r->last_hit && r->last_hit->mint < t) //previous was closer
            return 0;
        float3 normal;
        crossProduct(edge1, edge2, normal);
        normalize(normal, normal);
        float val = dotProduct(normal, r->dir);
        if(val < 0)
            val*=-1;
        if(val > 1)
            val = 1;
        //scale(color, val, color);
        ray_update_result(r, tri, t, normal, r->current_mesh->mats, (float3){1,1,1}, (float3){u, v, 1-u-v});
        return 1; // Hit, win
    }
    // This means that there is a line intersection but not a ray intersection. 
    return 0;
}
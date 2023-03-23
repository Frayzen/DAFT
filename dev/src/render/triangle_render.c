
#include "../../include/render/triangle_render.h"

int triangle_render(triangle * tri, mesh * m, ray * r) {
    float EPSILON = 0.0000001;
    float v0[3], v1[3], v2[3];
    get_vertex_from_triangle(m, tri, &v0, &v1, &v2);
    float edge1[3] = {v1.x - v0.x, v1.y - v0.y, v1.z - v0.z};
    float edge2[3] = {v2.x - v0.x, v2.y - v0.y, v2.z - v0.z};
    float h[3] = crossProduct(r->dir, edge2);
    float a = dotProduct(edge1, h);
    if (a > -EPSILON && a < EPSILON){
        return 0;    // This ray is parallel to this triangle.
    }
    float f = 1.0 / a;
    float s[3] = {r->pos.x - v0.x, r->pos.y - v0.y, r->pos.z - v0.z};
    float u = f * dotProduct(s, h);
    if (u < 0 || u > 1){
        return 0; // The intersection lies outside of the triangle
    }
    float q[3] = crossProduct(s, edge1);
    float v = f * dotProduct(r->dir, q);
    if (v < 0 || u+v > 1){
        return 0; // The intersection lies outside of the triangle
    }
    float t = f * dotProduct(edge2, q);
    if(t > EPSILON){
        if(r->last_hit && r->last_hit->mint < t) //previous was closer
            return;
        r->mint = t;
        r->tri = tri;
        r->m = m;
        float normal[3] = crossProduct(edge1, edge2);
        float val = dotProduct(normalize(normal), normalize(r->dir));
        if(val < 0)
            val*=-1;
        if(val > 1)
            val = 1;
        ray_hit(r, tri, mint, (float[3]){val, val, val});
        return 1; // Hit, win
    }
    return 0; // No hit, no win
}
#include "../../include/render/triangle_render.h"

int triangle_render(triangle * tri, ray * r) {
    mesh* m = r->current_mesh;
    float EPSILON = 0.0000001;
    float v0[3], v1[3], v2[3];
    get_vertex_from_triangle(m, tri, v0, v1, v2);
    float edge1[3];
    minus(v1, v0, edge1);
    float edge2[3];
    minus(v2, v0, edge2);
    float h[3];
    crossProduct(r->dir, edge2, h);
    float a = dotProduct(edge1, h);
    //show a
    if (a > -EPSILON && a < EPSILON){
        return 0;    // This ray is parallel to this triangle.
    }
    //print the vertices
    //print pos and dir of ray
    float f = 1.0 / a;
    float s[3];
    minus(r->pos, v0, s);
    float u = f * dotProduct(s, h);
    if (u < 0 || u > 1){
        return 0; // The intersection lies outside of the triangle
    }
    float q[3];
    crossProduct(s, edge1, q);
    float v = f * dotProduct(r->dir, q);
    if (v < 0 || u+v > 1){
        return 0; // The intersection lies outside of the triangle
    }
    float t = f * dotProduct(edge2, q);
    if(t > EPSILON){
        if(r->last_hit && r->last_hit->mint < t) //previous was closer
            return 0;
        float normal[3];
        crossProduct(edge1, edge2, normal);
        normalize(normal, normal);
        float ndir[3];
        normalize(r->dir, ndir);
        float val = dotProduct(normal, ndir);
        if(val < 0)
            val*=-1;
        if(val > 1)
            val = 1;
        ray_update_result(r, tri, t, (float[3]){1, 1, 1});
        return 1; // Hit, win
    }
    return 0; // No hit, no win
}
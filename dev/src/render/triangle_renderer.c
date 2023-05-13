#include "../../include/render/triangle_renderer.h"

void get_pixel_color(SDL_Surface* surface, int x, int y, Uint8* r, Uint8* g, Uint8* b)
{
  /*
  Retrieve the address to a specific pixel
  pSurface->pixels  = an array containing the SDL_Surface' pixels
  pSurface->pitch       = the length of a row of pixels (in bytes)
  X and Y               = the offset on where on the image to retrieve the pixel; (0, 0) is the upper left corner
  */
  Uint32 pixel = *( (Uint32*)surface->pixels + y * surface->w + x ) ;
  SDL_GetRGB(pixel, surface->format, r, g, b);
}

void get_color_at(ray* ry, float pos[3], triangle* tri, float* color, float u, float v, float w){
    mesh* m = ry->current_mesh;
    if(m->texture == NULL){
        color[0] = 1;
        color[1] = 1;
        color[2] = 1;
        return;
    }
    float* pt0 = m->texture_vertices[tri->vt[0]];
    float* pt1 = m->texture_vertices[tri->vt[1]];
    float* pt2 = m->texture_vertices[tri->vt[2]];
    float x = (pt0[0]*w + pt1[0]*u + pt2[0]*v);
    float y = (pt0[1]*w + pt1[1]*u + pt2[1]*v);
    int px = (int)(x * m->texture->w);
    int py = (int)((1-y) * m->texture->h);
    Uint8 r, g, b;
    get_pixel_color(m->texture, px, py, &r, &g, &b);
    color[0] = r/255.0;
    color[1] = g/255.0;
    color[2] = b/255.0;
}

int triangle_render(triangle* tri, ray* r){
    mesh* m = r->current_mesh;
    float EPSILON = 0.0000001;
    float v0[3], v1[3], v2[3];
    get_vertex_from_triangle(m, tri, v0, v1, v2);
    float edge1[3], edge2[3], h[3], s[3], q[3];
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
        float normal[3];
        crossProduct(edge1, edge2, normal);
        normalize(normal, normal);
        float val = dotProduct(normal, r->dir);
        if(val < 0)
            val*=-1;
        if(val > 1)
            val = 1;
        float color[3], pos[3];
        scale(r->dir, t, pos);
        get_color_at(r, pos, tri, color, u, v, 1-u-v);
        //scale(color, val, color);
        ray_update_result(r, tri, t, normal, r->current_mesh->mat);
        return 1; // Hit, win
    }
    // This means that there is a line intersection but not a ray intersection. 
    return 0;
}
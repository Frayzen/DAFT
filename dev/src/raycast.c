#include "../include/raycast.h"

void ray_intersect(triangle * tri, mesh * m, ray * r) {
    float EPSILON = 0.0000001;
    point v0, v1, v2;
    get_vertex_from_triangle(m, tri, &v0, &v1, &v2);
    //ppoint(v0, "V0");
    //ppoint(v1, "V1");
    //ppoint(v2, "V2");
    point edge1 = {v1.x - v0.x, v1.y - v0.y, v1.z - v0.z};
    point edge2 = {v2.x - v0.x, v2.y - v0.y, v2.z - v0.z};
    point h = crossProduct(r->dir, edge2);
    float a = dot(edge1, h);
    if (a > -EPSILON && a < EPSILON){
        return;    // This ray is parallel to this triangle.
    }
    float f = 1.0 / a;
    point s = {r->pos.x - v0.x, r->pos.y - v0.y, r->pos.z - v0.z};
    float u = f * dot(s, h);
    if (u < 0.0 || u > 1.0){
        return;
    }
    point q = crossProduct(s, edge1);
    float v = f * dot(r->dir, q);
    if (v < 0 || u+v > 1){
        return;
    }
    float t = f*dot(edge2, q);
    if(t > EPSILON){
        if(r->hit && r->mint < t)
            return;
        r->mint = t;
        r->tri = tri;
        r->m = m;
        point normal = crossProduct(edge1, edge2);
        float val = dot(normalize(normal), normalize(r->dir));
        if(val < 0)
            val*=-1;
        if(val > 1)
            val = 1;
        r->hit = 1;
        r->c.r =(int) 255*val;
        r->c.g =(int) 255*val;
        r->c.b =(int) 255*val;
        return;
    }
    // This means that there is a line intersection but not a ray intersection. 
    return;
}
int intersect_bbox(ray* r, bbox* b){
    float tmin = -INFINITY;
    float tmax = INFINITY;
    //    ppoint(b->max, "MAX");
    //    ppoint(b->min, "MIN");
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

int ray_cast(mesh* m, ray* r, bbox* b){
    if(intersect_bbox(r, b)){
        if(b->tris){
            for(size_t i = 0; i < b->c_size; i++)
                ray_intersect(&b->tris[i], m, r);
        }else{
            for(size_t i = 0; i < b->c_size; i++)
                ray_cast(m, r, b->children[i]);
        }
        return r->hit;
    }
    return 0;
}


void getPixelColor(SDL_Surface* surface, int x, int y, Uint8*r, Uint8*g,Uint8*b){
    Uint32 pixel = ((Uint32*)surface->pixels)[y*surface->w+x];
    SDL_GetRGB(pixel, surface->format, r,g,b);
}
ray get_ray(size_t width, size_t height, size_t x_pix, size_t y_pix, camera* cam){
    float yaw = cam->yaw;
    //float pitch = params.cam->pitch;
    float FOV = cam->FOV*M_PI/180;
    float hFOV = FOV/2;
    float pitch_ratio = (float)y_pix/(height-1);
    float yaw_ratio = (float)x_pix/(width-1);
    float deg1 = yaw+hFOV;
    float deg2 = yaw-hFOV;
    point p1 = npoint(cos(deg1), 0, sin(deg1));
    point p2 = npoint(cos(deg2), 0, sin(deg2));
    point flat = minus(p2, p1);
    point xz = add(p1, scale(flat, yaw_ratio));

    deg1 = hFOV;
    p1 = npoint(0, cos(deg1), 0);
    p2 = scale(p1, -1);
    flat = minus(p2, p1);
    point y = add(p1, scale(flat, pitch_ratio));
    point dir = add(xz, y);
    ray ry;
    ry.pos = cam->pos;
    ry.dir = dir;
    ry.hit = 0;
    return ry;
}
ray ray_cast_pixel(camera* cam, world* wd, size_t x, size_t y, size_t w, size_t h){
    ray ry = get_ray(w,h,x,y,cam);
    for(size_t idm = 0; idm <wd->size_m; idm++){
        mesh* m = wd->meshes[idm];
        ray_cast(m, &ry, m->bounding_box);
    }
    if(!ry.hit && cam->skybox != NULL){
        point dir = scale(normalize(ry.dir), -1);
        float u = 0.5+ (atan2f(dir.z, dir.x)/(M_PI*2));
        float v = 0.5+ (asinf(dir.y)/M_PI);
        SDL_Surface* skybox = cam->skybox;
        size_t x = u*skybox->w;
        size_t y = v*skybox->h;
        getPixelColor(skybox, x, y, &ry.c.r, &ry.c.g, &ry.c.b);
    }
    return ry;
}
int get_id(size_t w, size_t h, size_t x, size_t y){
    if(x < 0 || x >= w || y< 0 || y>=h)
        return -1;
    return w*y+x;
}

int cast_neighbour(ray *src, ray tgt){
    if(!tgt.hit)
        return 0;
    triangle* tri = tgt.tri;
    mesh* m = tgt.m;
    ray_intersect(tri, m, src);
    return src->hit;
}
ray ray_cast_neighbour(camera* cam, world* wd, size_t x, size_t y, size_t w, size_t h, ray rays[w*h]){
    ray ry = get_ray(w,h,x,y,cam);
    int l = get_id(w, h, x-1, y);
    if(l != -1 && cast_neighbour(&ry, rays[l]))
        return ry; 
    int u = get_id(w, h, x, y-1);
    if(u != -1 && cast_neighbour(&ry, rays[u]))
        return ry;
    int r = get_id(w, h, x+1, y);
    if(r != -1 && cast_neighbour(&ry, rays[r]))
        return ry;
    int b = get_id(w, h, x, y+1);
    if(b != -1 && cast_neighbour(&ry, rays[b]))
        return ry;
    if(!ry.hit && cam->skybox != NULL){
        point dir = scale(ry.dir, -1);
        float u = 0.5+ (atan2f(dir.x, dir.z)/(M_PI*2));
        float v = 0.5+ (asinf(dir.y)/M_PI);
        SDL_Surface* skybox = cam->skybox;
        size_t x = u*skybox->w;
        size_t y = v*skybox->h;
        getPixelColor(skybox, x, y, &ry.c.r, &ry.c.g, &ry.c.b);
    }
    return ry;
}

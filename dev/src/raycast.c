#include "../include/raycast.h"

void ray_intersect(triangle * tri, mesh * m, ray * r) {
    float EPSILON = 0.0000001;
    point v0 = *(m->vertexes[tri->vert[0]]);
    point v1 = *m->vertexes[tri->vert[1]];
    point v2 = *m->vertexes[tri->vert[2]];
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
        r->contact = add(r->pos, scale(r->dir, t));
        point normal = crossProduct(edge1, edge2);
        float val = dot(normalize(normal), normalize(r->dir));
        if(val < 0)
            val*=-1;
        if(val > 1)
            val = 1;
        r->hit = (int) 255*val;
        return;
    }
    // This means that there is a line intersection but not a ray intersection. 
    return;
}


void getPixelColor(SDL_Surface* surface, int x, int y, Uint8*r, Uint8*g,Uint8*b){
    Uint32 pixel = ((Uint32*)surface->pixels)[y*surface->w+x];
    SDL_GetRGB(pixel, surface->format, r,g,b);
}
color ray_cast_pixel(raycast_param params){
    float yaw = params.cam->yaw;
    //float pitch = params.cam->pitch;
    float FOV = params.cam->FOV*M_PI/180;
    float hFOV = FOV/2;
    float pitch_ratio = (float)params.y_pix/(params.height-1);
    float yaw_ratio = (float)params.x_pix/(params.width-1);

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
    ray* ry = init_ray(0, params.cam->pos, dir);
    world* wd = params.wd;
    float dist = -1;
    int v = 0;
    for(size_t id_mesh = 0; id_mesh < wd->size_m; id_mesh++){
        mesh* m = wd->meshes[id_mesh];
        for(size_t t_id = 0; t_id < m->t_size; t_id++){
            ray_intersect(m->triangles[t_id], m, ry);
            if(ry->hit){
                float cur = norm(minus(ry->pos, ry->contact));
                    if(cur < dist || dist == -1){
                        dist = cur;
                        v = ry->hit;
                    }
                ry->hit = 0;
            }
        }
    }
    color c;
    c.r = v;
    c.g = v;
    c.b = v;
    free(ry);
    if(!v && params.cam->skybox != NULL){
        dir = scale(dir, -1);
        float u = 0.5+ (atan2f(dir.x, dir.z)/(M_PI*2));
        float v = 0.5+ (asinf(dir.y)/M_PI);
        SDL_Surface* skybox = params.cam->skybox;
        size_t x = u*skybox->w;
        size_t y = v*skybox->h;
        getPixelColor(skybox, x, y, &c.r, &c.g, &c.b);
    }
    return c;
}

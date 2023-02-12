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
        r->contact = add(r->pos, scale(r->dir, t));
        point normal = crossProduct(edge1, edge2);
        float val = dot(normalize(normal), normalize(r->dir));
        if(val < 0)
            val*=-1;
        if(val > 1)
            val = 1;
        r->hit = (int) 255;
        return;
    }
    // This means that there is a line intersection but not a ray intersection. 
    return;
}
void intersect_bbox(mesh* m, ray* r, bbox* b){
    if(b->maxtotal < 100){
        r->hit = 255;
        return;
    }
    float tmin = -INFINITY;
    float tmax = INFINITY;
    r->hit = 0;
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
    //if(tmax < tmin)
        return;
    point contact;
    int hit_val = 0;
    float dist = -1;
    ray nr;
    nr.pos = r->pos;
    nr.dir = r->dir;
    nr.hit = 0;
    if(b->c_size != b->maxtotal){
        for(size_t i = 0; i < b->c_size; i++){
            intersect_bbox(m, &nr, b->children[i]);
            if(nr.hit){
               float curr_dist = norm(minus(nr.pos, nr.contact));
               if(curr_dist < dist){
                   dist = curr_dist;
                   hit_val = 255;
                   contact = nr.contact;
               }
            }
            nr.hit = 0;
        }
        r->contact = contact;
        r->hit = hit_val;
        if(b->maxtotal < 100)
            r->hit = 255;
        return;
    }else{
        for(size_t i = 0; i < b->c_size; i++){
            ray_intersect(&b->tris[i], m, &nr);
            if(nr.hit){
                //printf("HIT for %u\n", r->hit);
               float curr_dist = norm(minus(nr.pos, nr.contact));
               if(curr_dist < dist){
                   dist = curr_dist;
                   hit_val = 255;
                   contact = nr.contact;
               }
            }
            nr.hit = 0;
        }
        r->contact = contact;
        r->hit = hit_val;
        return;
    }
}

int ray_cast_pixel(raycast_param params){
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
    ray* ry = init_ray(params.cam->pos, dir);

    int v = 0;
    for(size_t idm = 0; idm < params.wd->size_m; idm++){
        mesh* m = params.wd->meshes[idm];
        intersect_bbox(m, ry, m->bounding_box);
        if(ry->hit)
            v = ry->hit; 
    }
    free(ry);
    return v;
}

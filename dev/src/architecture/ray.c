#include "../../include/architecture/ray.h"

void get_ray_direction(float* r, int width, int height, int x_pix, int y_pix, camera* cam){
    
    float yaw = cam->yaw;
    //float pitch = params.cam->pitch;
    float FOV = cam->FOV*M_PI/180;
    float hFOV = FOV/2;
    float pitch_ratio = (float)y_pix/(height-1);
    float yaw_ratio = (float)x_pix/(width-1);

    float deg1 = yaw+hFOV;
    float deg2 = yaw-hFOV;
    float p1[3] = {cos(deg1), 0, sin(deg1)}; 
    float p2[3] = {cos(deg2), 0, sin(deg2)};
    float flat[3], xz[3], dir[3], flat_scale[3];
    minus(p2, p1, flat);
    scale(flat, yaw_ratio, flat_scale);
    add(p1, flat_scale, xz);

    deg1 = FOV;
    float p3[3] = {0, cos(deg1), 0};
    float p4[3];
    scale(p3, -1, p4);
    minus(p4,p3,flat);
    scale(flat, pitch_ratio, flat_scale);
    float y[3];
    add(p3, flat_scale, y);
    add(xz, y, dir);
    normalize(dir, dir);
    copy(dir, r);
}
void update_sides(struct raycast_params* rcp){
    get_ray_direction(rcp->botLeftCorner, rcp->width, rcp->height, 0, 0, rcp->cam);
    float top[3], right[3], left[3], bot[3];
    get_ray_direction(top, rcp->width, rcp->height, 0, rcp->height-1, rcp->cam);
    get_ray_direction(right, rcp->width, rcp->height, rcp->width-1, 0, rcp->cam);
    get_ray_direction(left, rcp->width, rcp->height, 0, 0, rcp->cam);
    get_ray_direction(bot, rcp->width, rcp->height, 0, 0, rcp->cam);
    minus(top, bot, rcp->topDir);
    minus(right, left, rcp->rightDir);
    
}

void ray_update_result(ray* r, triangle* tri, float new_mint, float color[3]){
    ray_result* new_hit = calloc(sizeof(ray_result), 1); 
    new_hit->mint = new_mint;
    new_hit->tri = tri;
    new_hit->m = r->current_mesh;
    copy(color, new_hit->color);
    if(r->last_hit != NULL)
        free(r->last_hit);
    r->last_hit = new_hit;
}

ray create_ray_interpolate(raycast_params* rcp, int x_pix, int y_pix){
    ray r;
    float x_ratio = (float)x_pix/(rcp->width-1);
    float y_ratio = (float)y_pix/(rcp->height-1);
    copy(rcp->botLeftCorner, r.dir);
    float x[3], y[3];
    scale(rcp->rightDir, x_ratio, x);
    scale(rcp->topDir, y_ratio, y);
    add(r.dir, y, r.dir);
    add(r.dir, x, r.dir);
    normalize(r.dir, r.dir);
    r.last_hit = NULL;
    copy(rcp->cam->pos, r.pos);
    r.mint = INFINITY;
    return r;
}
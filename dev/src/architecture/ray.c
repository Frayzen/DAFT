#include "../../include/architecture/ray.h"

void get_ray_direction(float* r, int width, int height, int x_pix, int y_pix, camera* cam){
    float yaw = cam->yaw;
    float pitch = cam->pitch;
    float FOV_x = cam->FOV_x*M_PI/180;
    float FOV_y = cam->FOV_x*M_PI/180;
    float ratioX = ((float) x_pix/(float)  width) - 0.5;
    float ratioY = ((float) y_pix/(float) height) - 0.5;
    yaw += ratioX*FOV_x;
    pitch += ratioY*FOV_y;
    float dir[3] = {cos(pitch)*cos(yaw), sin(pitch), -cos(pitch)*sin(yaw)};
    copy(dir, r);
}
void update_sides(struct raycast_params* rcp){
    get_ray_direction(rcp->botLeftCorner, rcp->width, rcp->height, 0, rcp->width-1, rcp->cam);
    float top[3], right[3], left[3], bot[3];
    get_ray_direction(top, rcp->width, rcp->height, 0, rcp->height-1, rcp->cam);
    get_ray_direction(right, rcp->width, rcp->height, rcp->width-1, 0, rcp->cam);
    get_ray_direction(left, rcp->width, rcp->height, 0, 0, rcp->cam);
    get_ray_direction(bot, rcp->width, rcp->height, 0, 0, rcp->cam);
    minus(bot, top, rcp->topDir);
    minus(right, left, rcp->rightDir);
    
}

void ray_update_result(ray* r, triangle* tri, float new_mint, float color[3], float normal[3], float reflectivity){
    ray_result* new_hit = calloc(sizeof(ray_result), 1);
    new_hit->mint = new_mint;
    new_hit->tri = tri;
    new_hit->m = r->current_mesh;
    normalize(normal, new_hit->normal);
    new_hit->reflectivity = reflectivity;
    copy(color, new_hit->color);
    if(r->last_hit != NULL)
        free(r->last_hit);
    r->last_hit = new_hit;
}

ray create_ray_interpolate(raycast_params* rcp, int x_pix, int y_pix){
    ray r;
    float ratioX = ((float) x_pix/(float)  rcp->width);
    float ratioY = ((float) y_pix/(float) rcp->height);
    r.dir[0] = rcp->botLeftCorner[0] + ratioX*rcp->rightDir[0] + ratioY*rcp->topDir[0];
    r.dir[1] = rcp->botLeftCorner[1] + ratioX*rcp->rightDir[1] + ratioY*rcp->topDir[1];
    r.dir[2] = rcp->botLeftCorner[2] + ratioX*rcp->rightDir[2] + ratioY*rcp->topDir[2];
    r.last_hit = NULL;
    copy(rcp->cam->pos, r.pos);
    return r;
}
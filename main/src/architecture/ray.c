#include "../../include/architecture/ray.h"

void get_ray_direction(float *r, int width, int height, int x_pix, int y_pix, camera *cam)
{
    float yaw = cam->yaw;
    float pitch = cam->pitch;
    float FOV_x = cam->FOV_x * M_PI / 180;
    float FOV_y = cam->FOV_x * M_PI / 180;
    float ratioX = ((float)x_pix / (float)width) - 0.5;
    float ratioY = ((float)y_pix / (float)height) - 0.5;
    yaw += ratioX * FOV_x;
    pitch += ratioY * FOV_y;
    float dir[3] = {cos(pitch) * cos(yaw), sin(pitch), cos(pitch) * sin(yaw)};
    copy(dir, r);
}
void update_cam_sides(rendering_params *rdp)
{
    get_ray_direction(rdp->botLeftCorner, rdp->width, rdp->height, 0, rdp->width - 1, rdp->cam);
    float top[3], right[3], left[3], bot[3];
    get_ray_direction(top, rdp->width, rdp->height, 0, rdp->height - 1, rdp->cam);
    get_ray_direction(right, rdp->width, rdp->height, rdp->width - 1, 0, rdp->cam);
    get_ray_direction(left, rdp->width, rdp->height, 0, 0, rdp->cam);
    get_ray_direction(bot, rdp->width, rdp->height, 0, 0, rdp->cam);
    minus(bot, top, rdp->topDir);
    minus(right, left, rdp->rightDir);
}

void ray_update_result(ray *r, triangle *tri, float new_mint, float normal[3], material *mat, float color[3], float uvw[3])
{
    ray_result *new_hit = calloc(sizeof(ray_result), 1);
    new_hit->mint = new_mint;
    new_hit->tri = tri;
    new_hit->m = r->current_mesh;
    new_hit->mat = mat;
    if (uvw != NULL)
    {
        copy(uvw, new_hit->uvw);
    }
    else
    {
        new_hit->uvw[0] = 0;
        new_hit->uvw[1] = 0;
        new_hit->uvw[2] = 0;
    }
    copy(color, new_hit->color);
    copy(r->dir, new_hit->pos);
    scale(new_hit->pos, new_mint, new_hit->pos);
    add(new_hit->pos, r->pos, new_hit->pos);
    normalize(normal, new_hit->normal);
    if (r->last_hit != NULL)
        free(r->last_hit);
    r->last_hit = new_hit;
}

ray create_ray_interpolate(rendering_params *rdp, int x_pix, int y_pix)
{
    ray r;
    float ratioX = ((float)x_pix / (float)rdp->width);
    float ratioY = ((float)y_pix / (float)rdp->height);
    r.dir[0] = rdp->botLeftCorner[0] + ratioX * rdp->rightDir[0] + ratioY * rdp->topDir[0];
    r.dir[1] = rdp->botLeftCorner[1] + ratioX * rdp->rightDir[1] + ratioY * rdp->topDir[1];
    r.dir[2] = rdp->botLeftCorner[2] + ratioX * rdp->rightDir[2] + ratioY * rdp->topDir[2];
    r.last_hit = NULL;
    copy(rdp->cam->pos, r.pos);
    return r;
}
#include "../../include/architecture/ray.h"

void get_ray_direction(float3 *r, int width, int height, int x_pix, int y_pix, camera *cam)
{
    float yaw = cam->yaw;
    float pitch = cam->pitch;
    float FOV_x = cam->FOV_x * M_PI / 180;
    float FOV_y = cam->FOV_x * M_PI / 180;
    float ratioX = ((float)x_pix / (float)width) - 0.5;
    float ratioY = ((float)y_pix / (float)height) - 0.5;
    yaw += ratioX * FOV_x;
    pitch += ratioY * FOV_y;
    float3 dir = {cos(pitch) * cos(yaw), sin(pitch), cos(pitch) * sin(yaw)};
    copy(dir, (*r));
}
void update_cam_sides(rendering_params *rdp)
{
    get_ray_direction(&rdp->botLeftCorner, rdp->width, rdp->height, 0, rdp->width - 1, rdp->cam);
    float3 top, right, left, bot;
    get_ray_direction(&top, rdp->width, rdp->height, 0, rdp->height - 1, rdp->cam);
    get_ray_direction(&right, rdp->width, rdp->height, rdp->width - 1, 0, rdp->cam);
    get_ray_direction(&left, rdp->width, rdp->height, 0, 0, rdp->cam);
    get_ray_direction(&bot, rdp->width, rdp->height, 0, 0, rdp->cam);
    minus(bot, top, rdp->topDir);
    minus(right, left, rdp->rightDir);
}

void ray_update_result(ray *r, int tri, float new_mint, float3 normal, material *mat, float3 color, float3 uvw)
{
    ray_result *new_hit = calloc(sizeof(ray_result), 1);
    new_hit->mint = new_mint;
    new_hit->tri = tri;
    new_hit->m = r->current_mesh;
    new_hit->mat = mat;
    copy(uvw, new_hit->uvw);
    copy(color, new_hit->color);
    copy(r->dir, new_hit->pos);
    scale(new_hit->pos, new_mint, new_hit->pos);
    add(new_hit->pos, r->pos, new_hit->pos);
    new_hit->normal = normalize(normal);
    if (r->last_hit != NULL)
        free(r->last_hit);
    r->last_hit = new_hit;
}

ray create_ray_interpolate(rendering_params *rdp, int x_pix, int y_pix)
{
    ray r;
    float ratioX = ((float)x_pix / (float)rdp->width);
    float ratioY = ((float)y_pix / (float)rdp->height);

    r.dir.x = rdp->botLeftCorner.x + ratioX * rdp->rightDir.x + ratioY * rdp->topDir.x;
    r.dir.y = rdp->botLeftCorner.y + ratioX * rdp->rightDir.y + ratioY * rdp->topDir.y;
    r.dir.z = rdp->botLeftCorner.z + ratioX * rdp->rightDir.z + ratioY * rdp->topDir.z;
    
    r.last_hit = NULL;
    copy(rdp->cam->pos, r.pos);
    return r;
}
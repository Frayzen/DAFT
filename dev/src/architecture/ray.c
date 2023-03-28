#include "../../include/architecture/ray.h"

void create_ray(float* result, int width, int height, int x_pix, int y_pix, camera* cam){
    //float pitch = cam->pitch;
    float yaw = cam->yaw;
    float FOV = cam->FOV;

    FOV = FOV*M_PI/180;
    float hFOV = FOV/2;
    float pitch_ratio = (float)y_pix/(height-1);
    float yaw_ratio = (float)x_pix/(width-1);
    float deg1 = yaw+hFOV;
    float deg2 = yaw-hFOV;
    float p1[3] = {cos(deg1), 0, sin(deg1)};
    float p2[3] = {cos(deg2), 0, sin(deg2)};
    float flat[3], xz[3], dir[3];
    minus(p2, p1, flat);
    scale(flat, yaw_ratio, flat);
    add(p1, flat, xz);
    deg1 = hFOV;
    float p3[3] = {0, cos(deg1), 0};
    scale(p3, -1, p2);
    minus(p2, p3, flat);
    scale(flat, pitch_ratio, flat);
    float y[3];
    add(p3, flat, y);
    add(xz, y, dir);
    normalize(dir, dir);
    copy(dir, result);
}

void update_sides(struct raycast_params* rcp){
    create_ray(rcp->leftSide, rcp->width, rcp->height, 0, rcp->height/2, rcp->cam);
    create_ray(rcp->rightSide, rcp->width, rcp->height, rcp->width, rcp->height/2, rcp->cam);
    create_ray(rcp->topSide, rcp->width, rcp->height, rcp->width/2, 0, rcp->cam);
    create_ray(rcp->botSide, rcp->width, rcp->height, rcp->width/2, rcp->height, rcp->cam);
}

ray* init_rays(struct raycast_params* rdr){
    int width = rdr->width;
    int height = rdr->height;
    camera* cam = rdr->cam;
    ray* rays = calloc(sizeof(ray), width * height);
    #pragma omp parallel for
    for(int j = 0; j < height; j++){
        #pragma omp parallel for
        for(int i = 0; i < width; i++){
            create_ray(rays[i+j*width].dir, width, height, i, j, cam);
            copy(cam->pos, rays[i+j*width].pos);
            rays[i+j*width].last_hit = malloc(sizeof(ray_result));
            
        }
    }
    
    return rays;
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
    float xaxis[3];
    float yaxis[3];
    add(rcp->rightSide, rcp->leftSide, xaxis);
    scale(xaxis, x_pix/(float)rcp->width, xaxis);
    add(rcp->botSide, rcp->topSide, yaxis);
    scale(yaxis, y_pix/(float)rcp->height, yaxis);
    add(xaxis, yaxis, r.dir);
    normalize(r.dir, r.dir);
    r.last_hit = NULL;
    copy(rcp->cam->pos, r.pos);
    r.mint = INFINITY;
    return r;
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
    float p1[3] = {cos(deg1), 0, sin(deg1)}; 
    float p2[3] = {cos(deg2), 0, sin(deg2)};
    float flat[3], xz[3], dir[3], flat_scale[3];
    minus(p2, p1, flat);
    scale(flat, yaw_ratio, flat_scale);
    add(p1, flat_scale, xz);

    deg1 = hFOV;
    float p3[3] = {0, cos(deg1), 0};
    float p4[3];
    scale(p3, -1, p4);
    minus(p4,p3,flat);
    scale(flat, pitch_ratio, flat_scale);
    float y[3];
    add(p3, flat_scale, y);
    add(xz, y, dir);
    ray ry;
    ry.last_hit = NULL;
    copy(dir, ry.dir);
    copy(cam->pos, ry.pos);
    ry.mint = INFINITY;
    return ry;
}
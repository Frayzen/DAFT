#include "../../include/render/rasterizer.h"

void rasterize_bbox(mesh*m, rendering_params* rdp, int* pixels){
    //TODO: redo
    float3 minp = m->b_min[0];
    float3 maxp = m->b_max[0];

    //rasterize the bbox
    float3 p1 = {minp.x, minp.y, minp.z};
    float3 p2 = {minp.x, minp.y, maxp.z};
    float3 p3 = {minp.x, maxp.y, minp.z};
    float3 p4 = {minp.x, maxp.y, maxp.z};
    float3 p5 = {maxp.x, minp.y, minp.z};
    float3 p6 = {maxp.x, minp.y, maxp.z};
    float3 p7 = {maxp.x, maxp.y, minp.z};
    float3 p8 = {maxp.x, maxp.y, maxp.z};
    float3 points[8] = {p1, p2, p3, p4, p5, p6, p7, p8};

    float minrp = 2;
    float maxrp = -1;
    float mintp = 2;
    float maxtp = -1;

    float3 normal;
    add(rdp->topDir, rdp->botLeftCorner, normal);
    add(rdp->rightDir, normal, normal);
    add(rdp->botLeftCorner, normal, normal);
    scale(normal, 0.5, normal);

    for(int i = 0; i < 8; i++){
        float3 p = points[i];
        float3 dir;
        minus(p, rdp->cam->pos, dir);
        dir = normalize(dir);
        float proj = project(dir, normal);
        if(proj < 0)
            continue;
        scale(dir, 1/proj, dir);
        float rproj = project(dir, rdp->rightDir)+0.5;
        float tproj = project(dir, rdp->topDir)+0.5;

        if(rproj < minrp)
            minrp = rproj;
        if(rproj > maxrp)
            maxrp = rproj;
        if(tproj < mintp)
            mintp = tproj;
        if(tproj > maxtp)
            maxtp = tproj;
    }

    if(mintp > maxtp || minrp > maxrp || maxtp < 0 || maxrp < 0 || mintp > 1 || minrp > 1){
        return;
    }

    int fromx = max(minrp * rdp->width, 0);
    int tox = min(maxrp * rdp->width, rdp->width);
    int fromy = max(mintp * rdp->height, 0);
    int toy = min(maxtp * rdp->height, rdp->height);
    for(int i = fromy; i < toy; i++){
        memset(pixels + i * rdp->width + fromx, 1, (tox - fromx) * sizeof(int));
    }

}


float plane_line_intersect(float3 plane_normal, float3 plane_point, float3 line_point, float3 line_dir)
{
    float3 neg;
    minus(plane_point, line_point, neg);
    float t = (dotProduct(neg, plane_normal))/(dotProduct(line_dir, plane_normal));
    return t;
}

 
float screen_project(sphere *s, rendering_params * rdp, int * index, float3 screen_pos)
{
    float3 plane_normal;
    crossProduct(rdp->topDir, rdp->rightDir, plane_normal);
    float3 ray_dir;
    minus(s->pos, rdp->cam->pos, ray_dir);
    float3 plane_point;
    copy(rdp->botLeftCorner, plane_point);
    add(plane_point, rdp->cam->pos, plane_point);
    float t = plane_line_intersect(plane_normal, plane_point, rdp->cam->pos, ray_dir);
    
    scale(ray_dir, t, ray_dir);
    add(ray_dir, rdp->cam->pos, ray_dir); //now ray dir hows the point on te screen
    copy(ray_dir, screen_pos);
   
    return s->radius*distance(screen_pos, rdp->cam->pos)/ distance(s->pos, rdp->cam->pos) ;
 
}


void rasterize_sphere(sphere* s, rendering_params* rdp, int* pixels){
    // int index;
    // float3 screen_pos;
    // float radius = screen_project(s, rdp, &index, screen_pos);
    // if(radius < 0){
    //     return;
    // }
    // radius*=1.5;
    // float3 pixel_pos;
    // int tot_pixels = rdp->width * rdp->height;
    // int x;
    // int y;
    // float ratioX;
    // float ratioY;
    // for (int i = 0; i < tot_pixels; i++)
    // {
    //     if (pixels[i])
    //         continue;
    //     y = i / rdp->width;
    //     x = i % rdp->width;
    //     ratioX = ((float) x/(float)  rdp->width);
    //     ratioY = ((float) y/(float) rdp->height);

    //     pixel_pos[1] = rdp->botLeftCorner[1] + ratioX*rdp->rightDir[1] + ratioY*rdp->topDir[1];
    //     pixel_pos[2] = rdp->botLeftCorner[2] + ratioX*rdp->rightDir[2] + ratioY*rdp->topDir[2];
    //     pixel_pos[0] = rdp->botLeftCorner[0] + ratioX*rdp->rightDir[0] + ratioY*rdp->topDir[0];
    //     add(pixel_pos, rdp->cam->pos, pixel_pos);
    //     if (distance(pixel_pos, screen_pos) < radius)
    //         pixels[i] |= SPHERE_MASK; 
    // } 
}

void render_rasterize(rendering_params* rdp, int* pixels){
    world* w = rdp->w;
    for(int i = 0; i < w->size_meshes; i++){
        rasterize_bbox(w->meshes[i], rdp, pixels);
    }
    

}
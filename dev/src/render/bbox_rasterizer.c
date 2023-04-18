#include "../../include/render/bbox_rasterizer.h"

void rasterize_bbox(mesh* m, raycast_params* rcp, int* pixels){
    bbox* b = m->box;

    //rasterize the bbox
    float p1[3] = {b->min[0], b->min[1], b->min[2]};
    float p2[3] = {b->min[0], b->min[1], b->max[2]};
    float p3[3] = {b->min[0], b->max[1], b->min[2]};
    float p4[3] = {b->min[0], b->max[1], b->max[2]};
    float p5[3] = {b->max[0], b->min[1], b->min[2]};
    float p6[3] = {b->max[0], b->min[1], b->max[2]};
    float p7[3] = {b->max[0], b->max[1], b->min[2]};
    float p8[3] = {b->max[0], b->max[1], b->max[2]};
    float* points[8] = {p1, p2, p3, p4, p5, p6, p7, p8};

    float minrp = 2;
    float maxrp = -1;
    float mintp = 2;
    float maxtp = -1;

    float normal[3];
    add(rcp->topDir, rcp->botLeftCorner, normal);
    add(rcp->rightDir, normal, normal);
    add(rcp->botLeftCorner, normal, normal);
    scale(normal, 0.5, normal);

    for(int i = 0; i < 8; i++){
        float* p = points[i];
        float dir[3];
        minus(p, rcp->cam->pos, dir);
        normalize(dir, dir);
        float proj = project(dir, normal);
        if(proj < 0)
            continue;
        scale(dir, 1/proj, dir);
        float rproj = project(dir, rcp->rightDir)+0.5;
        float tproj = project(dir, rcp->topDir)+0.5;

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

    int fromx = max(minrp * rcp->width, 0);
    int tox = min(maxrp * rcp->width, rcp->width);
    int fromy = max(mintp * rcp->height, 0);
    int toy = min(maxtp * rcp->height, rcp->height);

    //printf("fromx : %d, tox : %d, fromy : %d, toy : %d", fromx, tox, fromy, toy);

    //set all values between minu and maxu in x and mint and maxt in y to 1 using memset
    for(int i = fromy; i < toy; i++){
        memset(pixels + i * rcp->width + fromx, 1, (tox - fromx) * sizeof(int));
    }

}

void render_rasterize_bbox(raycast_params* rcp, int* pixels){
    world* w = rcp->w;
    for(int i = 0; i < w->size_meshes; i++){
        rasterize_bbox(w->meshes[i], rcp, pixels);
    }
}
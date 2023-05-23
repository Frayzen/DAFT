#include "../../include/render/rasterizer.h"


int project_on_screen(float* p, rendering_params* rdp, int* x, int* y){
    float pos[3];
    minus(p, rdp->cam->pos, pos);
    normalize(pos, pos);
    float pitch = asin(pos[1]);
    float yaw = atan2(pos[2], pos[0]);
    float begin_pitch = rdp->cam->pitch - rdp->FOV_y/2;
    float begin_yaw = rdp->cam->yaw - rdp->FOV_x/2;
    float end_pitch = rdp->cam->pitch + rdp->FOV_y/2;
    float end_yaw = rdp->cam->yaw + rdp->FOV_x/2;
    float ratio_x = (yaw - begin_yaw)/(end_yaw - begin_yaw);
    float ratio_y = (pitch - begin_pitch)/(end_pitch - begin_pitch);
    if(ratio_x < 0 || ratio_x > 1 || ratio_y < 0 || ratio_y > 1){
        return 0;
    }
    *x = ratio_x*rdp->width;
    *y = ratio_y*rdp->height;
    return 1;
}

void rasterize_bbox(bbox* b, rendering_params* rdp, int* pixels){
    //TODO: redo


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
    add(rdp->topDir, rdp->botLeftCorner, normal);
    add(rdp->rightDir, normal, normal);
    add(rdp->botLeftCorner, normal, normal);
    scale(normal, 0.5, normal);

    for(int i = 0; i < 8; i++){
        float* p = points[i];
        float dir[3];
        minus(p, rdp->cam->pos, dir);
        normalize(dir, dir);
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

    //printf("fromx : %d, tox : %d, fromy : %d, toy : %d", fromx, tox, fromy, toy);

    //set all values between minu and maxu in x and mint and maxt in y to 1 using memset
    for(int i = fromy; i < toy; i++){
        memset(pixels + i * rdp->width + fromx, 1, (tox - fromx) * sizeof(int));
    }

}
int inside_ellipse(int x, int y, int cx, int cy, int rx, int ry){
    float a = (x-cx);
    float b = (y-cy);
    return a*a / (float)(rx*rx) + b*b/(float)(ry*ry) <= 1;
}

void fill_elipse(int from_x, int from_y, int rx, int ry, rendering_params* rdp, int* pixels){
    printf("fill ellipse from %d %d with %d %d\n", from_x, from_y, rx, ry);
    for(int x = max(0, from_x); x < min(rdp->width, from_x + rx); x++){
        for(int y = max(0, from_y); y < min(rdp->height, from_y + ry); y++){
            if(inside_ellipse(x, y, from_x, from_y, rx, ry)){
                pixels[y*rdp->width + x] |= SPHERE_MASK;
            }
        }
    }
}

void rasterize_sphere(sphere* s, rendering_params* rdp, int* pixels){
    int x, y;
    float spos[3];
    copy(s->pos, spos);
    if(!project_on_screen(spos, rdp, &x, &y))
        return;
    float radius = (float) s->radius;
    float dist = distance(spos, rdp->cam->pos);
    float r_ratio = radius/dist;
    int rw = r_ratio*rdp->width;
    int rh = r_ratio*rdp->height;
    fill_elipse(x, y, rw, rh, rdp, pixels);
}

void render_rasterize(rendering_params* rdp, int* pixels){
    world* w = rdp->w;
    for(int i = 0; i < w->size_meshes; i++){
        rasterize_bbox(w->meshes[i]->box, rdp, pixels);
    }
    for(int i = 0; i < w->size_lights; i++){
        rasterize_sphere(w->lights[i]->s, rdp, pixels);
    }
}
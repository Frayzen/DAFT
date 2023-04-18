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

    float minu = 1;
    float maxu = 0;
    float mint = 1;
    float maxt = 0;

    float right[3], top[3];
    normalize(rcp->rightDir, right);
    normalize(rcp->topDir, top);

    for(int i = 0; i < 8; i++){
        float* p = points[i];
        float v[3];
        minus(p, rcp->cam->pos, v);
        minus(p, rcp->botLeftCorner, v);
        float nv = normSquared(v);
        float t = dotProduct(v, right);
        float u = dotProduct(v, top);
        u/=nv;
        t/=nv;
        if(u < minu)
            minu = u;
        if(u > maxu)
            maxu = u;
        if(t < mint)
            mint = t;
        if(t > maxt)
            maxt = t;
    }


    if(maxu < minu || maxt < mint)
        return;

    int fromx = max(mint*rcp->width, 0);
    int tox = min(maxt*rcp->width, rcp->width);
    int fromy = max(minu*rcp->height, 0);
    int toy = min(maxu*rcp->height, rcp->height);


    //set all values between minu and maxu in x and mint and maxt in y to 1
    for(int x = fromx; x < tox; x++){
        for(int y = fromy; y < toy; y++){
            pixels[y*rcp->width+x] = 1;
        }
    }

}

void render_rasterize_bbox(raycast_params* rcp, int* pixels){
    world* w = rcp->w;
    for(int i = 0; i < w->size_meshes; i++){
        rasterize_bbox(w->meshes[i], rcp, pixels);
    }
}
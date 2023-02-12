#include "../include/bbox.h"
#include "../include/utils.h"
void take_min(point* p, point o){
    p->x = p->x < o.x ? p->x : o.x;
    p->y = p->y < o.y ? p->y : o.y;
    p->z = p->z < o.z ? p->z : o.z;
}
void take_max(point* p, point o){
    p->x = p->x > o.x ? p->x : o.x;
    p->y = p->y > o.y ? p->y : o.y;
    p->z = p->z > o.z ? p->z : o.z;
}
void compute_bounds_tri(mesh* m, bbox *bx){
    point a, b, c;
    get_vertex_from_triangle(m, &(bx->tris[0]), &a, &b, &c);
    bx->min = a;
    bx->max = a;
    for(size_t i = 0; i < bx->c_size; i++){
        get_vertex_from_triangle(m, &(bx->tris[i]), &a, &b, &c);
        take_min(&bx->min, a);
        take_min(&bx->min, b);
        take_min(&bx->min, c);
        take_max(&bx->max, a);
        take_max(&bx->max, b);
        take_max(&bx->max, c);
    }
}
void compute_bounds_bbox(bbox* b){
    b->min = b->children[0]->min;
    b->max = b->children[1]->max;
    for(size_t i = 0; i < b->c_size; i++){
        take_min(&b->min, b->children[i]->min);
        take_max(&b->max, b->children[i]->max);
    }
    ppoint(b->min,"NEW MIN");
}
bbox* init_bbox(){
    bbox * b = malloc(sizeof(bbox));
    memset(b, 0, sizeof(bbox));
    return b;
}
size_t compute_depth(size_t nb_tri){
    size_t depth = 0;

    while (nb_tri > 0)
    {
        nb_tri /= LBBOX;
        depth++;
    }
    return depth;
}

size_t compute_tri_last_level(size_t depth, size_t no_tri)
{
    return no_tri/pow(LBBOX, depth-1);
}

size_t compute_no_extra(size_t no_tri, size_t tri_last_level, size_t depth)
{
    return no_tri-tri_last_level*pow(LBBOX, depth-1);
}
///nbcnr is number of children of next recursion
bbox* build_bbox(size_t depth, size_t no_tri, size_t no_extra)
{
    bbox* b = init_bbox();
    if (depth == 1)
    {
        b->tris = malloc(sizeof(triangle) *(no_extra + no_tri));
        b->c_size  = no_extra + no_tri;
        b->maxtotal = b->c_size;
        return b;
    }
    else
    {
        b->children = malloc(sizeof(bbox*)*LBBOX);
        b->c_size = LBBOX;
        size_t nbcnr = pow(LBBOX, depth-2);
        for (size_t i = 0; i < LBBOX; i++)
        {
            b->children[i] = build_bbox(depth-1, no_tri, no_extra < nbcnr ? no_extra : nbcnr);
            if(no_extra > nbcnr)
                no_extra -= nbcnr;
            else
                no_extra = 0;
            b->maxtotal+=b->children[i]->maxtotal;
        }
        return b;
    }
}
void add_tri_to_bbox(mesh* m, bbox *b, size_t depth, triangle *t){
    if(depth == 1){
        b->tris[b->total] = *t;
        b->total++;
        if(b->total == b->maxtotal)
            compute_bounds_tri(m, b);
        return;
    }
    size_t j = 0;
    b->total++;
    while(b->children[j]->total == b->children[j]->maxtotal)
        j++;
    add_tri_to_bbox(m, b->children[j], depth-1, t);
    if(b->total == b->maxtotal)
        compute_bounds_bbox(b);
    return;
}
void free_bbox(bbox* b){
    if(!b | !b->tris)
        return;
    for(size_t i = 0; i < b->c_size; i++){
        free_bbox(b->children[i]);
    }
    free(b);
}

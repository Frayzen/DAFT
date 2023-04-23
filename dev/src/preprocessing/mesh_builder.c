#include "../../include/preprocessing/mesh_builder.h"

void add_v(mesh * m, float v[3])
{
    m->vertices[m->nb_vertices] = malloc(sizeof(float)*3);
    copy(v, m->vertices[m->nb_vertices]);
	m->nb_vertices++;
}

void add_vt(mesh * m, int vt[2]){
    m->texture_vertices[m->nb_texture_vertices] = malloc(sizeof(int)*2);
    m->texture_vertices[m->nb_texture_vertices][0] = vt[0];
	m->texture_vertices[m->nb_texture_vertices][1] = vt[1];
	m->nb_texture_vertices++;
}

void add_vn(mesh * m, float vn[3])
{
    m->normal_vertices[m->nb_normal_vertices] = malloc(sizeof(float)*3);
    copy(vn, m->normal_vertices[m->nb_normal_vertices]);
	m->nb_normal_vertices++;
}

void take_min(float p[3], float o[3]){
    p[0] = p[0] < o[0] ? p[0] : o[0];
    p[1] = p[1] < o[1] ? p[1] : o[1];
    p[2] = p[2] < o[2] ? p[2] : o[2];
}
void take_max(float p[3], float o[3]){
    p[0] = p[0] > o[0] ? p[0] : o[0];
    p[1] = p[1] > o[1] ? p[1] : o[1];
    p[2] = p[2] > o[2] ? p[2] : o[2];
}
void compute_bounds_tri(mesh* m, bbox *bx){
    float a[3], b[3], c[3];
    get_vertex_from_triangle(m, &(bx->tris[0]), a, b, c);
    copy(a, bx->min);
    copy(a, bx->max);
    for(int i = 0; i < bx->c_size; i++){
        get_vertex_from_triangle(m, &(bx->tris[i]), a, b, c);
        take_min(bx->min, a);
        take_min(bx->min, b);
        take_min(bx->min, c);
        take_max(bx->max, a);
        take_max(bx->max, b);
        take_max(bx->max, c);
    }
}
void compute_bounds_bbox(bbox* b){
    copy(b->children[0]->min,b->min);
    copy(b->children[1]->max,b->max);
    for(int i = 0; i < b->c_size; i++){
        take_min(b->min, b->children[i]->min);
        take_max(b->max, b->children[i]->max);
    }
}
bbox* init_bbox(){
    bbox * b = calloc(sizeof(bbox), 1);
    return b;
}
int compute_depth(int nb_tri){
    int depth = 0;

    while (nb_tri > 0)
    {
        nb_tri /= LBBOX;
        depth++;
    }
    return depth;
}

int compute_tri_last_level(int depth, int no_tri)
{
    return no_tri/pow(LBBOX, depth-1);
}

int compute_no_extra(int no_tri, int tri_last_level, int depth)
{
    return no_tri-tri_last_level*pow(LBBOX, depth-1);
}
///nbcnr is number of children of next recursion
bbox* build_bbox(int depth, int no_tri, int no_extra)
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
        int nbcnr = pow(LBBOX, depth-2);
        for (int i = 0; i < LBBOX; i++)
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
void add_tri_to_bbox(mesh* m, bbox *b, int depth, int v[3], int vt[3], int vn[3]){
    if(depth == 1){
        for(int i = 0; i < 3; i++){
            b->tris[b->total].v[i] = v[i];
            b->tris[b->total].vt[i] = vt[i];
            b->tris[b->total].vn[i] = vn[i];
        }
        b->total++;
        if(b->total == b->maxtotal)
            compute_bounds_tri(m, b);
        return;
    }
    int j = 0;
    b->total++;
    while(b->children[j]->total == b->children[j]->maxtotal)
        j++;
    add_tri_to_bbox(m, b->children[j], depth-1, v, vt, vn);
    if(b->total == b->maxtotal)
        compute_bounds_bbox(b);
    return;
}
void add_tri(mesh* m, int v[3], int vt[3], int vn[3]){
    add_tri_to_bbox(m, m->box, m->depth, v, vt, vn);
    m->nb_triangles++;
}
mesh * build_mesh(int no_vert, int no_tri, int text_vert)
{
    mesh * m = (mesh *)malloc(sizeof(mesh));
    m->depth = compute_depth(no_tri-1);
    m->tri_last_level = compute_tri_last_level(m->depth, no_tri);
    m->no_extra = compute_no_extra(no_tri, m->tri_last_level, m->depth);
    m->box = build_bbox(m->depth, m->tri_last_level, m->no_extra);
	m->nb_vertices = 0;
    m->nb_triangles = 0;
    m->nb_texture_vertices = 0;
	m->vertices = malloc(sizeof(float*)*no_vert);
	m->normal_vertices = malloc(sizeof(float*)*text_vert);
	return m;
}

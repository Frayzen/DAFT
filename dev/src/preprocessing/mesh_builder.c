#include "../../include/preprocessing/mesh_builder.h"
void add_tri(mesh* m, int3 v, int3 vt, int3 vn, int mat){
    m->tri_v[m->tri_size] = v;
    m->tri_t[m->tri_size] = vt;
    m->tri_n[m->tri_size] = vn;
    m->tri_m[m->tri_size] = mat;
    m->tri_size++;
}

void add_v(mesh * m, float3 v)
{
    copy(v, m->vs[m->vs_size]);
    m->vs_size++;
}

void add_vt(mesh * m, float2 vt){
    copy2(vt, m->vt[m->vt_size]);
    m->vt_size++;
}

void add_vn(mesh * m, float3 vn)
{
    copy(vn, m->vn[m->vn_size]);
    m->vn_size++;
}

void take_min(float3* a, float3 b){
    float3 p = *a;
    p.x = p.x < b.x ? p.x : b.x;
    p.y = p.y < b.y ? p.y : b.y;
    p.z = p.z < b.z ? p.z : b.z;
}
void take_max(float3* a, float3 b){
    float3 p = *a;
    p.x = p.x > b.x ? p.x : b.x;
    p.y = p.y > b.y ? p.y : b.y;
    p.z = p.z > b.z ? p.z : b.z;
}

int compute_depth(int no_tri){
    int depth = 0;
    while(no_tri > LBBOX){
        depth++;
        no_tri/=LBBOX;
    }
    return depth;
}

int build_bboxes(mesh* m, int cur_depth, int* cur_tri){
    int id = m->bboxes_size;
    define(m->b_min[id], INFINITY, INFINITY, INFINITY);
    define(m->b_max[id], -INFINITY, -INFINITY, -INFINITY);
    m->bboxes_size++;
    if(cur_depth == 0){
        for (size_t i = 0; i < LBBOX; i++)
        {
            if(*cur_tri >= m->tri_size)
                return id;
            m->b_children[id*LBBOX+i] = *cur_tri;
            float3 pts[3];
            get_v_from_tri(m, *cur_tri, pts);
            for (size_t j = 0; j < 3; j++)
            {
                take_min(&m->b_min[id], pts[j]);
                take_max(&m->b_max[id], pts[j]);
            }
            *cur_tri = *cur_tri + 1;
        }
        return id;
    }
    for(int i = 0; i < LBBOX; i++){
        m->b_children[id*LBBOX+i] = build_bboxes(m, cur_depth-1, cur_tri);
        take_min(&m->b_min[id], m->b_min[m->b_children[id*LBBOX+i]]);
        take_max(&m->b_max[id], m->b_max[m->b_children[id*LBBOX+i]]);
    }
    return id;
}

mesh * init_mesh(int no_vert, int no_tri, int text_vert, int norm_vert)
{
    mesh * m = malloc(sizeof(mesh));
    assert(m != NULL);
    assert(m != NULL);
    m->vs_size = 0;
    m->vs = malloc(sizeof(float3)*no_vert);
    assert(m->vs != NULL);
    m->vt_size = 0;
    m->vt = malloc(sizeof(int2)*text_vert);
    assert(m->vt != NULL);
    m->vn_size = 0;
    m->vn = malloc(sizeof(float3)*norm_vert);
    assert(m->vn != NULL);

    m->tri_size = 0;
    m->tri_v = malloc(sizeof(int3)*no_tri);
    assert(m->tri_v != NULL);
    m->tri_t = malloc(sizeof(int3)*no_tri);
    assert(m->tri_t != NULL);
    m->tri_n = malloc(sizeof(int3)*no_tri);
    assert(m->tri_n != NULL);
    m->tri_m = malloc(sizeof(int)*no_tri);
    assert(m->tri_m != NULL);
    
    int depth = compute_depth(no_tri);
    int nb_bboxes = pow(LBBOX, depth);
    m->bboxes_size = 0;
    m->b_min = calloc(sizeof(float3),nb_bboxes);
    assert(m->b_min != NULL);

    m->b_max = calloc(sizeof(float3),nb_bboxes);
    assert(m->b_max != NULL);

    m->b_children = malloc(sizeof(int)*nb_bboxes*LBBOX);
    assert(m->b_children != NULL);
    
    m->mat_size = 0;
    m->mats = NULL;
	return m;
}
void build_mesh(mesh* m){
    int cur_tri = 0;
    int depth = compute_depth(m->tri_size);
    build_bboxes(m, depth, &cur_tri);
}
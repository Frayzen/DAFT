#include "../../include/architecture/mesh.h"

void free_mesh(mesh* msh){
    free(msh->b_children);
    free(msh->b_max);
    free(msh->b_min);
    free(msh->tri_n);
    free(msh->tri_t);
    free(msh->tri_v);
    free(msh->vn);
    free(msh->vt);
    free(msh->vs);
    free_mat(msh->mats);
    free(msh);
}

void get_vt_from_tri(mesh* m, int tri, float2 vt[3]){
    vt[0] = m->vt[m->tri_t[tri].p1];
    vt[1] = m->vt[m->tri_t[tri].p2];
    vt[2] = m->vt[m->tri_t[tri].p3];
}

void get_vn_from_tri(mesh* m, int tri, float3 vn[3]){
    vn[0] = m->vn[m->tri_n[tri].p1];
    vn[1] = m->vn[m->tri_n[tri].p2];
    vn[2] = m->vn[m->tri_n[tri].p3];
}

void get_v_from_tri(mesh* m, int tri, float3 v[3]){
    //printf("tri %d p1 %d p2 %d p3 %d\n", tri, m->tri_v[tri].p1, m->tri_v[tri].p2, m->tri_v[tri].p3);
    v[0] = m->vs[m->tri_v[tri].p1];
    v[1] = m->vs[m->tri_v[tri].p2];
    v[2] = m->vs[m->tri_v[tri].p3];
}
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
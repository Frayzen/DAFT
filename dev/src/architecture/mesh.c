#include "../../include/architecture/mesh.h"

mesh* init_mesh(){
    mesh* msh = calloc(sizeof(mesh), 1);
    return msh;
}

void free_mesh(mesh* msh){
    free(msh);
}
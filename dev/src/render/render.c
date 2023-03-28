#include "../../include/render/render.h"

void ray_cast(ray* r, world* w){
    for(int idm = 0; idm < w->size_meshes; idm++){
        mesh* m = w->meshes[idm];
        r->current_mesh = m;
        mesh_render(m, r);
    }
}
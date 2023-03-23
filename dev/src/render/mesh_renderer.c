#include "../../include/render/mesh_renderer.h"

int mesh_render(mesh* m, ray *r)
{
    for(size_t idm = 0; idm <wd->size_m; idm++){
        mesh* m = wd->meshes[idm];
        bbox_render(m->bounding_box, r);
    }
    return ry->last_hit;
}
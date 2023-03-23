#include "../../include/render/mesh_renderer.h"

int mesh_render(mesh* m, ray *r)
{
    return bbox_render(m->box, r);
}
#include "../../include/render/render.h"

void ray_cast(ray* r, world* w){
    for(size_t idm = 0; idm < w->size_meshes; idm++){
        mesh* m = w->meshes[idm];
        r->current_mesh = m;
        mesh_render(m, r);
    }
}

ray ray_cast_for_pixel(camera* cam, world* wd, size_t x, size_t y, size_t w, size_t h){
    ray ry = get_ray(w,h,x,y,cam->FOV, cam->yaw, cam->pitch, cam->pos);
    ray_cast(&ry, wd);
    // if(!ry.hit && cam->skybox != NULL){
    //     get_sky(ry.dir, cam, &ry.c);
    // }
    // TODO
    return ry;
}
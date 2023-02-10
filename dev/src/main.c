#include "../include/image_renderer.h"
#include "../include/obj_parser.h"
#include "../include/raycast.h"
#include <stdio.h>
int main(){
    world* wd = init_world();
    load_object(wd, "assets/objs/cube.obj", .5, npoint(4, .1, .5));
   
    for(size_t i = 0; i < wd->size_m; i++){
        mesh* m = wd->meshes[i];
        for(size_t mi = 0; mi < m->v_size; mi++){
            point* p = m->vertexes[mi];
            printf("Pt %lu : %f %f %f\n", mi, p->x, p->y, p->z);
        }
        for(size_t mi = 0; mi < m->t_size; mi++){
            triangle* t = m->triangles[mi];
            printf("FACE %lu : %lu %lu %lu\n", mi, t->vert[0], t->vert[1], t->vert[2]);
        }
    }
    

    printf("WORDL OBJ COUNT: %lu \n", wd->size_m);
    camera* cam = init_camera(0, npoint(0,0,0), 0, 0, 120);
    app_params params;
    params.width = 200;
    params.height = 200;
    raycast_param rp;
    rp.cam = cam;
    rp.x_pix = params.width/2 - 1;
    rp.y_pix = params.height/2 - 1;
    rp.width = params.width;
    rp.height = params.height;
    rp.wd = wd;
    ray_cast_pixel(rp);
    params.wd = wd;
    params.cam = cam;
    params.FPS_UPPER_LIMIT=30;
    if(setup_window(&params))
        return 1;

    render_camera(&params);
    free(cam);
    free_world(wd);
    return 0;
}

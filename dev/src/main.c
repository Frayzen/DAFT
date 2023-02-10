#include "../include/image_renderer.h"
#include "../include/obj_parser.h"
#include "../include/raycast.h"
#include <stdio.h>
int main(){
    world* wd = init_world();
    load_object(wd, "assets/objs/cube.obj", .5, npoint(0,0,0));
   
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
    params.width = 500;
    params.height = 500;
    params.wd = wd;
    params.cam = cam;
    params.FPS_UPPER_LIMIT=30;
    if(setup_window(&params))
        return 1;
    cam->skybox = IMG_Load("assets/textures/Nebula.png");
    render_camera(&params);
    free(cam);
    free_world(wd);
    return 0;
}

#include "../include/image_renderer.h"
#include "../include/obj_parser.h"
#include <stdio.h>
int main(){
    world* wd = init_world();
    load_object(wd, "assets/objs/cube.obj", 1);
    printf("WORDL OBJ COUNT: %lu \n", wd->size_m);
    camera* cam = init_camera(0, npoint(0,0,0), 0, 0);
    app_params params;
    params.width = 800;
    params.height = 500;
    params.wd = wd;
    params.cam = cam;
    params.FPS_UPPER_LIMIT=30;
    if(setup_window(&params))
        return 1;
    render_camera(&params);
    free_world(wd);
    return 0;
}

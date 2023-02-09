#include "../include/image_renderer.h"
#include "../include/obj_parser.h"
#include <stdio.h>
int main(){
    world* world = init_world();
    load_object(world, "assets/objs/cube.obj", 1);
    camera* cam = init_camera(0, npoint(0,0,0), normalize(npoint(0, 1, 0)));
    app_params params;
    params.width = 800;
    params.height = 500;
    params.world = world;
    params.cam = cam;
    params.FPS_UPPER_LIMIT=30;
    if(setup_window(&params))
        return 1;
    render_camera(&params);
    return 0;
}

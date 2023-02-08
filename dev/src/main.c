#include "../include/image_renderer.h"
#include "../include/obj_parser.h"
#include <stdio.h>
int main(){
    world* world = init_world();
    load_object(world, "assets/objs/cube.obj", 1);
    app_params params;
    params.width = 800;
    params.height = 500;
    params.FPS_UPPER_LIMIT=30;
    setup_renderer(&params);
    launch(&params);
    return 0;
}

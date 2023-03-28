#include <stdio.h>
#include "../include/constants.h"
#include <stdlib.h>
#include "../include/architecture/world.h"
#include "../include/window/window.h"
#include "../include/architecture/camera.h"
#include "../include/preprocessing/obj_parser.h"

int main(){
    world* wd = init_world();
    printf("LOADING OBJ...");
    load_object(wd, "assets/objs/cube.obj", 1, (float[]){0,0,0});
    printf("WORDL OBJ COUNT: %d \n", wd->size_meshes);
    camera* cam = init_camera((float[]){-8,0,0}, 90, 0, 120, NULL);
    add_camera(wd, cam);   

    app_params params;
    params.width = 500;
    params.height = 500;
    params.wd = wd;
    params.cam = cam;
    params.FPS_UPPER_LIMIT=30;

    if(setup_window(&params))
        return 1;

    cam->skybox = IMG_Load("assets/textures/Sky.jpg");
    launch_screen(&params);
    free_window(&params);
    free_world(wd);
    return 0;
}

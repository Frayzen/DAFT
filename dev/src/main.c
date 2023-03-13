#include <stdio.h>
#include "../include/constants.h"
#include <stdlib.h>
#include "../include/architecture/world.h"
#include "../include/window/window.h"
#include "../include/architecture/camera.h"

int main(){
    world* wd = init_world();
    printf("LOADING OBJ...");

    printf("OK\n");
    printf("WORDL OBJ COUNT: %d \n", wd->size_meshes);

    camera* cam = init_camera((float[]){0,0,0}, 0, 0, 120, NULL);

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
    free(cam);
    free_world(wd);
    return 0;
}

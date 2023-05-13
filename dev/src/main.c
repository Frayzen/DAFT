#include <stdio.h>
#include <stdlib.h>
#include "../include/constants.h"
#include "../include/architecture/world.h"
#include "../include/window/window.h"
#include "../include/window/skybox.h"
#include "../include/architecture/camera.h"
#include "../include/architecture/ray.h"
#include "../include/preprocessing/obj_parser.h"

int main(){
    world* wd = init_world();
    camera* cam = init_camera((float[]){-4,0,0}, 0, 0, 90, 90);
    add_camera(wd, cam);
    app_params params;
    params.width = 150;
    params.height = 150;
    params.screen_scale = 5;
    params.wd = wd;
    params.cam = cam;
    params.FPS_UPPER_LIMIT=30;

    if(setup_window(&params))
        return 1;

    printf("World initialized, loading objects\n");

    sphere* s = sphere_init(0, 0, 0, 1, def_mat(1,0,0,0,0));
    add_sphere(wd, s);
    // CHALLENGE : load_object("assets/objs/bunny.obj", wd, 10, (float[]){0,0,0}, .1);
    //1166 875 -> 388, 218
    //load_object("./assets/objs/grass.obj", wd, 1, (float[]){0,0,0}, NULL, .2);
    //load_object("./assets/objs/katana.obj", wd, 4, (float[]){0,0,0}, "./assets/textures/katana.png", 0);
    light* lt = init_light((float[]){0,3,0}, illum(1,1,1,1.2));
    add_light(wd, lt);
    light* lt2 = init_light((float[]){-4,0,0}, illum(1,1,1, 1000));
    add_light(wd, lt2);

    printf("World object count: %d \n", wd->size_meshes);
    load_skybox(wd, "./assets/skybox/Sky.jpg");
    launch_screen(&params);
    free_window(&params);
    free_world(wd);
    return 0;
}

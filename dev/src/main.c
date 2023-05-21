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
    params.width = 100;
    params.height = 100;
    params.screen_scale = 10;
    params.wd = wd;
    params.cam = cam;
    params.FPS_UPPER_LIMIT=30;

    if(setup_window(&params))
        return 1;

    printf("World initialized, loading objects\n");

    // sphere* s = sphere_init(0, 0, 0, 1, def_mat(1,1,1,4,.1));
    // add_sphere(wd, s);
    // CHALLENGE : load_object("assets/objs/bunny.obj", wd, 10, (float[]){0,0,0}, .1);
    //1166 875 -> 388, 218
    //load_object("./assets/objs/grass.obj", wd, 1, (float[]){0,-1,0}, "./assets/textures/grass.png", def_mat(1,1,1,100,.1));
    load_object("./assets/objs/teddy.obj", wd, .1, (float[]){0,0,0}, NULL, def_mat(1,1,1,3,0));
    //light* lt = init_light((float[]){0,3,0}, illum(1,1,1,1.2));
    //add_light(wd, lt);
    light* lt2 = init_light((float[]){-10,0,0}, (float[]){1,1,1});
    add_light(wd, lt2);

    printf("World object count: %d \n", wd->size_meshes);
    load_skybox(wd, "./assets/skybox/Sky.jpg");
    launch_screen(&params);
    free_window(&params);
    free_world(wd);
    return 0;
}   

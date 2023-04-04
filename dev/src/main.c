#include <stdio.h>
#include <stdlib.h>
#include "../include/constants.h"
#include "../include/architecture/world.h"
#include "../include/window/window.h"
#include "../include/architecture/camera.h"
#include "../include/architecture/ray.h"
#include "../include/preprocessing/obj_parser.h"

int main(){
    world* wd = init_world();
    printf("LOADING OBJ...");
    printf("WORDL OBJ COUNT: %d \n", wd->size_meshes);
    camera* cam = init_camera((float[]){-2,0,0}, 0, 0, 90, 90);
    add_camera(wd, cam);
    sphere* s = sphere_init(0, 2, 0, 0.5, .5, 0 ,0, 1);
    add_sphere(wd, s);
    load_object("assets/objs/cube.obj", wd, 1, (float[]){0,0,0}, .1);
    load_object("assets/objs/cube.obj", wd, .5, (float[]){4,0.5,0}, .3);
    load_object("assets/objs/cube.obj", wd, .5, (float[]){-4,0.5,0}, .5);
    load_object("assets/objs/cube.obj", wd, .5, (float[]){0,0.5,4}, .7);
    load_object("assets/objs/cube.obj", wd, .5, (float[]){0,0.5,-4}, 1);
    light* lt = init_light((float[]){0,5,0}, (float[]){1,1,1}, 1);
    add_light(wd, lt);
    
    app_params params;
    params.width = 200;
    params.height = 200;
    params.wd = wd; 
    params.cam = cam;
    params.FPS_UPPER_LIMIT=30;

    if(setup_window(&params))
        return 1;

    load_skybox(wd, "assets/textures/Sky.jpg");
    launch_screen(&params);
    free_window(&params);
    free_world(wd);
    return 0;
}

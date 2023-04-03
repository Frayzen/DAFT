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
    load_object(wd, "assets/objs/car.obj", .1, (float[]){0,0,0}, 1);
    //load_object(wd, "assets/objs/cube.obj", 1, (float[]){0,0,0}, .4);
    printf("WORDL OBJ COUNT: %d \n", wd->size_meshes);
    camera* cam = init_camera((float[]){-2,0,0}, 0, 0, 90, 90);
    add_camera(wd, cam);
    int bound = 3;
    for(int i = 0; i < bound; i++){
        for(int j = 0; j < bound; j++){
            for(int k = 0; k < bound; k++){
                 sphere* s = sphere_init(i,j,k,0.3*((i+j+k)%2+1),(i+k)%2,(i+j)%2,(j+k)%2,.7);
                add_sphere(wd, s);
            }
        }
    }

    app_params params;
    params.width = 100;
    params.height = 100;
    params.wd = wd; 
    params.cam = cam;
    params.FPS_UPPER_LIMIT=30;

    if(setup_window(&params))
        return 1;

    load_skybox(wd, "assets/textures/Studio.jpg");
    launch_screen(&params);
    free_window(&params);
    free_world(wd);
    return 0;
}

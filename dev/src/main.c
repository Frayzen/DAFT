#include <stdio.h>
#include <stdlib.h>
#include "../include/constants.h"
#include "../include/architecture/world.h"
#include "../include/window/window.h"
#include "../include/window/skybox.h"
#include "../include/architecture/camera.h"
#include "../include/architecture/ray.h"
#include "../include/preprocessing/obj_parser.h"
#include "../include/preprocessing/mtl_parser.h"

int main(int argc, char** argv){

    if (argc < 2)
        errx(EXIT_FAILURE, "The name of the .obj file is missing.");
    else if (argc > 2)
        errx(EXIT_FAILURE, "Specify only one file");

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
    //material* materials;
    //int p = 0;
    //mtl_parser("./assets/materials/capsule.mtl", &materials, &p);
    load_object(argv[1], wd, 1, (float[]){0,0,0}, "./assets/textures/capsule0.jpg");
    /*printf("ambient %f %f %f\n", materials[0].ambient[0], materials[0].ambient[1], materials[0].ambient[2]);
    printf("diffuse %f %f %f\n", materials[0].diffuse[0], materials[0].diffuse[1], materials[0].diffuse[2]);
    printf("specular %f %f %f\n",materials[0].specular[0], materials[0].specular[1], materials[0].specular[2]);

    printf("ambient %f %f %f\n", materials[1].ambient[0], materials[1].ambient[1], materials[1].ambient[2]);
    printf("diffuse %f %f %f\n", materials[1].diffuse[0], materials[1].diffuse[1], materials[1].diffuse[2]);q
    printf("specular %f %f %f\n",materials[1].specular[0], materials[1].specular[1], materials[1].specular[2]);*/
    load_object(argv[1], wd, 1, (float[]){0,0,0}, NULL, materials);

    free(materials);
    /*for (int i = 0; i < numMaterials; i++) {
        printf("Material #%d\n", i + 1);
        printf("Name: %s\n", materials[i].name);
        printf("Ambient: %f %f %f\n", materials[i].ambient[0], materials[i].ambient[1], materials[i].ambient[2]);
        printf("Diffuse: %f %f %f\n", materials[i].diffuse[0], materials[i].diffuse[1], materials[i].diffuse[2]);
        printf("Specular: %f %f %f\n", materials[i].specular[0], materials[i].specular[1], materials[i].specular[2]);
        printf("Shininess: %f\n", materials[i].shininess);
        printf("Reflection: %f\n", materials[i].reflection);
        printf("\n");
    }*/


    /*free(mat[0]);
    free(mat[1]);
    free(mat);*/

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

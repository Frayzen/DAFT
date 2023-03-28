#include "../../include/architecture/world.h"

world* init_world(){
    world* wd = calloc(sizeof(world), 1);
    return wd;
}

void free_world(world* wd){
    for(int i = 0; i < wd->size_meshes; i++){
        free_mesh(wd->meshes[i]);
    }
    for(int i = 0; i < wd->size_lights; i++){
        free_light(wd->lights[i]);
    }
    free(wd->lights);
    for(int i = 0; i < wd->size_cameras; i++){
        free_camera(wd->cameras[i]);
    }
    free(wd->cameras);
    free(wd->lights);
    free(wd->meshes);
    free(wd);
}

void add_camera(world* wd, camera* cam){
    wd->size_cameras++;
    wd->cameras = realloc(wd->cameras, sizeof(camera*) * wd->size_cameras);
    wd->cameras[wd->size_cameras - 1] = cam;
}
void add_light(world* wd, light* lt){
    wd->size_lights++;
    wd->lights = realloc(wd->lights, sizeof(light*) * wd->size_lights);
    wd->lights[wd->size_lights - 1] = lt;
}
void add_mesh(world* wd, mesh* msh){
    wd->size_meshes++;
    wd->meshes = realloc(wd->meshes, sizeof(mesh*) * wd->size_meshes);
    wd->meshes[wd->size_meshes - 1] = msh;
}
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
    for(int i = 0; i < wd->size_cameras; i++){
        free(wd->cameras[i]);
    }
    if(wd->skybox != NULL){
        SDL_FreeSurface(wd->skybox);
    }
    free(wd->cameras);
    free(wd->lights);
    free(wd->meshes);
    free(wd->spheres);
    free(wd->campoints);
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
void add_sphere(world* wd, sphere* s){
    wd->size_spheres++;
    wd->spheres = realloc(wd->spheres, sizeof(sphere) * wd->size_spheres);
    wd->spheres[wd->size_spheres - 1] = *s;
}

void add_campoint(world* wd, campoint* cp){
    wd->size_campoints++;
    wd->campoints = realloc(wd->campoints, sizeof(campoint) * wd->size_campoints);
    wd->campoints[wd->size_campoints - 1] = *cp;
}
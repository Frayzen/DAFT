#include <stdio.h>
#include <SDL2/SDL.h>
#include <stdlib.h>
#include "../include/preprocessing/scene_parser.h"
#include "../include/window/window.h"

int main(int argc, char *argv[]){
    if(argc<2){
        printf("Usage: %s <scene_file>\n", argv[0]);
        return 1;
    }
    world *wd = load_scene(argv[1]);
    app_params params;
    params.width = 100;
    params.height = 100;
    params.screen_scale = 10;
    params.wd = wd;
    if(wd->size_cameras != 0)
        params.cam = wd->cameras[0];
    params.FPS_UPPER_LIMIT=30;
    if(setup_window(&params))
        return 1;
    launch_screen(&params);
    free_window(&params);
    free_world(wd);
    return 0;
}   

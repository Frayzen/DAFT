#include "../include/image_renderer.h"
#include "../include/obj_parser.h"
#include <stdio.h>
int main(int argc, char *argv[]){
    if(argc < 2){
        printf("Usage: ./DAFT <obj_file> <scale> <skybox>\n");
        return 0;
    }
    world* wd = init_world();
    printf("LOADING OBJ...");
    float size = 1;
    if(argc > 2)
        size = atof(argv[2]);
    load_object(wd, argv[1], size, npoint(0,0,0));
   
    for(size_t i = 0; i < wd->size_m; i++){
        mesh* m = wd->meshes[i];
        printf("OBJ loaded with a depth of %lu\n", m->depth);
        printf("OBJ loaded with a c_size of %lu\n", m->bounding_box->c_size);
        printf("OBJ loaded with a max and total of %lu %lu\n", m->bounding_box->maxtotal, m->bounding_box->total);
        printf("OBJ bounding_box points: (max then min) for c_size %lu\n", m->bounding_box->c_size);
        ppoint(m->bounding_box->min, "MIN");
        ppoint(m->bounding_box->max, "MAX");
    }

    printf("WORDL OBJ COUNT: %lu \n", wd->size_m);
    camera* cam = init_camera(0, npoint(0,0,0), 0, 0, 120);
    app_params params;
    params.width = 500;
    params.height = 500;
    params.wd = wd;
    params.cam = cam;
    params.FPS_UPPER_LIMIT=30;
    if(setup_window(&params))
        return 1;
    if(argc > 3)
        cam->skybox = IMG_Load(argv[3]);
    render_camera(&params);
    free(cam);
    free_world(wd);
    return 0;
}

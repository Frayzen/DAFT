#include "../../include/window/event_handler.h"

void launch_quality_render(app_params* params){
    camera* quality_cam = malloc(sizeof(camera));
    copy(params->cam->pos, quality_cam->pos);
    quality_cam->FOV = 90;
    quality_cam->yaw = params->cam->yaw;
    quality_cam->pitch = params->cam->pitch;
    quality_cam->skybox = params->cam->skybox;
    raycast_params* quality_rcp = init_raycast_params(params->wd, QUALITY_WIDTH, QUALITY_HEIGHT, quality_cam, NULL);
    printf("COPYING...\n");
    render_quality(quality_rcp);
}

void handle_key(SDL_Keycode key, app_params* params){
    switch (key)
    {
        case SDLK_SPACE:
            launch_quality_render(params);
            break;
        default:
            break;
    }
}

void handle_events(SDL_Event event, int* quit, app_params* params){
    switch (event.type)
    {
        case SDL_QUIT:
            *quit = 1;
            break;
        case SDL_KEYDOWN:
            handle_key(event.key.keysym.sym, params);
        default:
            break;
    }
}
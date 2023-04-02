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

//pressed = 1 if key is pressed, 0 if released
void handle_key(SDL_Keycode key, app_params* params, int pressed){
    float delta = MOVING_SPEED;
    if(!pressed)
        delta*=-1;
    switch (key)
    {
        case SDLK_p:
            if(pressed)
                launch_quality_render(params);
            break;
        case SDLK_w:
            params->cam->movement_speed[0] += delta;
            break;
        case SDLK_s:
            params->cam->movement_speed[0] -= delta;
            break;
        case SDLK_a:
            params->cam->movement_speed[1] += delta;
            break;
        case SDLK_d:
            params->cam->movement_speed[1] -= delta;
            break;
        case SDLK_SPACE:
            params->cam->movement_speed[2] += delta;
            break;
        case SDLK_LSHIFT:
            params->cam->movement_speed[2] -= delta;
            break;
        default:
            break;
    }
    for(int i = 0; i < 3; i++){
        if(params->cam->movement_speed[i] > MOVING_SPEED){
            params->cam->movement_speed[i] = MOVING_SPEED;
        }
        if(params->cam->movement_speed[i] < -MOVING_SPEED){
            params->cam->movement_speed[i] = -MOVING_SPEED;
        }
    }
}

void handle_events(int* quit, app_params* params){
    SDL_Event event;
    if(SDL_PollEvent(&event)){
        switch (event.type)
        {
            case SDL_QUIT:
                *quit = 1;
                break;
            case SDL_KEYDOWN:
                handle_key(event.key.keysym.sym, params, 1);
                break;
            case SDL_KEYUP:
                handle_key(event.key.keysym.sym, params, 0);
                break;
            case SDL_MOUSEMOTION:
                params->cam->yaw += event.motion.xrel/100.0;
                if(params->cam->yaw > 2*M_PI)
                    params->cam->yaw -= 2*M_PI;
                if(params->cam->yaw < 0)
                    params->cam->yaw += 2*M_PI;
                break;
            default:
                break;
        }
    }
    float forward[3] = {cos(params->cam->yaw), 0, sin(params->cam->yaw)};
    float right[3] = {cos(params->cam->yaw+M_PI/2), 0, sin(params->cam->yaw+M_PI/2)};
    float up[3] = {0, 1, 0};
    scale(forward, params->cam->movement_speed[0], forward);
    scale(right, params->cam->movement_speed[1], right);
    scale(up, params->cam->movement_speed[2], up);

    add(params->cam->pos, forward, params->cam->pos);
    add(params->cam->pos, right, params->cam->pos);
    add(params->cam->pos, up, params->cam->pos);
}
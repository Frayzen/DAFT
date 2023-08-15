#include "../../include/window/event_handler.h"

void clamp(float* value, float min, float max){
    if(*value < min)
        *value = min;
    if(*value > max)
        *value = max;
}

//pressed = 1 if key is pressed, 0 if released
void handle_key(SDL_Keycode key, app_params* params, int pressed){
    float delta = MOVING_SPEED;
    if(!pressed)
        delta*=-1;
    switch (key)
    {
        case SDLK_w:
            params->cam->movement_speed.x += delta;
            break;
        case SDLK_s:
            params->cam->movement_speed.x -= delta;
            break;
        case SDLK_a:
            params->cam->movement_speed.y -= delta;
            break;
        case SDLK_d:
            params->cam->movement_speed.y += delta;
            break;
        case SDLK_SPACE:
            params->cam->movement_speed.z += delta;
            break;
        case SDLK_LSHIFT:
            params->cam->movement_speed.z -= delta;
            break;
        default:
            break;
    }

    clamp(&params->cam->movement_speed.x, -MOVING_SPEED, MOVING_SPEED);
    clamp(&params->cam->movement_speed.y, -MOVING_SPEED, MOVING_SPEED);
    clamp(&params->cam->movement_speed.z, -MOVING_SPEED, MOVING_SPEED);
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
                params->cam->rotation_speed.x = event.motion.xrel;
                break;
            default:
                break;
        }
    }
    float yaw = params->cam->angles.x;
    Vector3 forward = {cos(yaw), 0, sin(yaw)};
    Vector3 right = {cos(yaw+M_PI/2), 0, sin(yaw+M_PI/2)};
    Vector3 up = {0, 1, 0};
    forward = scale(forward, params->cam->movement_speed.x);
    right = scale(right, params->cam->movement_speed.y);
    up = scale(up, params->cam->movement_speed.z);
    params->cam->pos = add(forward, params->cam->pos);
    params->cam->pos = add(right, params->cam->pos);
    params->cam->pos = add(up, params->cam->pos);
    params->cam->angles.x += params->cam->rotation_speed.x/100;
    params->cam->rotation_speed.x = 0;
}
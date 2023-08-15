#include "../../include/window/event_handler.h"

void clamp(float* value, float min, float max){
    if(*value < min)
        *value = min;
    if(*value > max)
        *value = max;
}

//pressed = 1 if key is pressed, 0 if released
void handle_key(SDL_Keycode key, DaftApp* app, int pressed){
    float delta = MOVING_SPEED;
    if(!pressed)
        delta*=-1;
    switch (key)
    {
        case SDLK_w:
            app->camera->movement_speed.x += delta;
            break;
        case SDLK_s:
            app->camera->movement_speed.x -= delta;
            break;
        case SDLK_a:
            app->camera->movement_speed.y -= delta;
            break;
        case SDLK_d:
            app->camera->movement_speed.y += delta;
            break;
        case SDLK_SPACE:
            app->camera->movement_speed.z += delta;
            break;
        case SDLK_LSHIFT:
            app->camera->movement_speed.z -= delta;
            break;
        default:
            break;
    }

    clamp(&app->camera->movement_speed.x, -MOVING_SPEED, MOVING_SPEED);
    clamp(&app->camera->movement_speed.y, -MOVING_SPEED, MOVING_SPEED);
    clamp(&app->camera->movement_speed.z, -MOVING_SPEED, MOVING_SPEED);
}

void handle_events(int* quit, DaftApp* app){
    SDL_Event event;
    if(SDL_PollEvent(&event)){
        switch (event.type)
        {
            case SDL_QUIT:
                *quit = 1;
                break;
            case SDL_KEYDOWN:
                handle_key(event.key.keysym.sym, app, 1);
                break;
            case SDL_KEYUP:
                handle_key(event.key.keysym.sym, app, 0);
                break;
            case SDL_MOUSEMOTION:
                app->camera->rotation_speed.x = event.motion.xrel;
                app->camera->rotation_speed.y = event.motion.yrel;
                break;
            default:
                break;
        }
    }
    float yaw = app->camera->rotation.x;
    Vector3 forward = {cos(yaw), 0, sin(yaw)};
    Vector3 right = {cos(yaw+M_PI/2), 0, sin(yaw+M_PI/2)};
    Vector3 up = {0, 1, 0};
    forward = scale(forward, app->camera->movement_speed.x);
    right = scale(right, app->camera->movement_speed.y);
    up = scale(up, app->camera->movement_speed.z);
    app->camera->position = add(forward, app->camera->position);
    app->camera->position = add(right, app->camera->position);
    app->camera->position = add(up, app->camera->position);
    app->camera->rotation.y -= app->camera->rotation_speed.x/100;
    app->camera->rotation.x += app->camera->rotation_speed.y/100;
    clamp(&app->camera->rotation.x, -M_PI/4, M_PI/4);
    app->camera->rotation_speed.x = 0;
    app->camera->rotation_speed.y = 0;
}
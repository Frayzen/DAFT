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
        case FORW_KEY:
            app->camera->movement_speed.x += delta;
            break;
        case BACK_KEY:
            app->camera->movement_speed.x -= delta;
            break;
        case RIGHT_KEY:
            app->camera->movement_speed.z += delta;
            break;
        case LEFT_KEY:
            app->camera->movement_speed.z -= delta;
            break;
        case UP_KEY:
            app->camera->movement_speed.y += delta;
            break;
        case DOWN_KEY:
            app->camera->movement_speed.y -= delta;
            break;
        case SDLK_f:
            printf("Children: %d, %d\n", app->world->meshes[0]->children[0].x, app->world->meshes[0]->children[0].y);
            break;
        case SDLK_g:
            printf("Bounds min : %f %f %f\n", app->world->meshes[0]->minBbox[0].x, app->world->meshes[0]->minBbox[0].y, app->world->meshes[0]->minBbox[0].z);
            printf("Bounds max : %f %f %f\n", app->world->meshes[0]->maxBbox[0].x, app->world->meshes[0]->maxBbox[0].y, app->world->meshes[0]->maxBbox[0].z);
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
    float yaw = app->camera->rotation.y;
    Matrix3 rotationMatrix = createRotationMatrix(app->camera->rotation);
    Vector3 forward = multiplyMatrixVector(rotationMatrix, VECTOR_FORWARD);
    Vector3 up = multiplyMatrixVector(rotationMatrix, VECTOR_UP);
    Vector3 right = multiplyMatrixVector(rotationMatrix, VECTOR_RIGHT);

    forward = scalef(forward, app->camera->movement_speed.x);
    up = scalef(up, app->camera->movement_speed.y);
    right = scalef(right, app->camera->movement_speed.z);
    app->camera->position = add(forward, app->camera->position);
    app->camera->position = add(right, app->camera->position);
    app->camera->position = add(up, app->camera->position);
    app->camera->rotation.y -= app->camera->rotation_speed.x/100;
    //app->camera->rotation.z -= app->camera->rotation_speed.y/100;
    clamp(&app->camera->rotation.z, -M_PI/4, M_PI/4);
    app->camera->rotation_speed.x = 0;
    app->camera->rotation_speed.y = 0;
}
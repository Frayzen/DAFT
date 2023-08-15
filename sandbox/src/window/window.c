#include "../../include/window/window.h"
#include "../../include/window/event_handler.h"

int setup_window(app_params* params){
    omp_set_num_threads(omp_get_num_procs());
    SDL_Init(SDL_INIT_VIDEO);
    IMG_Init(IMG_INIT_PNG);
    SDL_SetHint( SDL_HINT_RENDER_SCALE_QUALITY, "1" );
    
    params->window = SDL_CreateWindow("SDL2 Displaying Image",
            SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
            params->width * params->screen_scale, params->height * params->screen_scale, 0);
    params->renderer = SDL_CreateRenderer(params->window, -1, SDL_RENDERER_ACCELERATED);
    SDL_SetRelativeMouseMode(SDL_TRUE);
    SDL_RendererInfo info;
    SDL_GetRendererInfo(params->renderer, &info );
    //pixels
    params->texture = SDL_CreateTexture(params->renderer, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_STREAMING, params->width, params->height);
    Uint32* pixels;
    int pitch;
    SDL_LockTexture(params->texture, NULL, (void**)&pixels, &pitch);
    return 0;
}

void free_window(app_params* params){
    SDL_DestroyRenderer(params->renderer); 
    SDL_DestroyWindow(params->window);
    SDL_DestroyTexture(params->texture);
    SDL_Quit();
}

int launch_screen(app_params* params){
    int quit = 0;
    time_t last = time(NULL);
    int fps = 0;
    // float angle = 0;
    // float ro = 5;
    SDL_Texture* texture = SDL_CreateTextureFromSurface(params->renderer, params->wd->skybox);
    while (!quit)
    {
        //quit = 1;
        // params->cam->pos[0] = ro*cos(angle);
        // params->cam->pos[2] = ro*sin(angle);
        // params->cam->yaw = M_PI-angle;
        // angle+=0.003;
        // if(angle > 2*M_PI){
        //     angle -= 2*M_PI;
        // }
        
        render_screen();
        SDL_UnlockTexture(params->texture);
        if(params->wd->skybox != NULL){
            define_sky_points(params->renderer, texture, params->wd);
            SDL_SetTextureBlendMode(params->texture, SDL_BLENDMODE_BLEND);
        }
        SDL_RenderCopy(params->renderer, params->texture, NULL, NULL); 
        SDL_RenderPresent(params->renderer);
        fps++;
        if(last != time(NULL)){
            printf("%i fps\n", fps);
            fps = 0;
            last = time(NULL);
        }
        handle_events(&quit, params);
    }
    return 0;
}


#include "../../include/window/window.h"

int setup_window(app_params* params){
    omp_set_num_threads(omp_get_num_procs());
    SDL_Init(SDL_INIT_VIDEO);
    IMG_Init(IMG_INIT_PNG);
    SDL_SetHint( SDL_HINT_RENDER_SCALE_QUALITY, "1" );
    params->window = SDL_CreateWindow("SDL2 Displaying Image",
            SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
            params->width, params->height ,0);
    params->renderer = SDL_CreateRenderer(params->window, -1, SDL_RENDERER_ACCELERATED);
    SDL_RendererInfo info;
    SDL_GetRendererInfo(params->renderer, &info );
    printf("Renderer Name: %s\n", info.name);
    for(Uint32 i = 0; i < info.num_texture_formats; i++){
        printf("Format: %s\n", SDL_GetPixelFormatName(info.texture_formats[i]));
    }
    //pixels
    params->texture = SDL_CreateTexture(params->renderer, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_STREAMING, params->width, params->height);
    Uint32* pixels;
    int pitch;
    SDL_LockTexture(params->texture, NULL, (void**)&pixels, &pitch);
    params->rcp = init_raycast_params(params->wd, params->width, params->height, params->cam, pixels);
    //camera
    SDL_Surface* old = params->cam->skybox;
    params->cam->skybox = SDL_ConvertSurfaceFormat(old, SDL_PIXELFORMAT_RGBA8888, 0);
    SDL_FreeSurface(old);
    return 0;
}

void free_window(app_params* params){
    free_raycast_params(params->rcp);
    SDL_DestroyRenderer(params->renderer); 
    SDL_DestroyWindow(params->window);
    SDL_DestroyTexture(params->texture);
    SDL_Quit();
}

int launch_screen(app_params* params){
    int quit = 0;
    SDL_Event event;
    time_t last = time(NULL);
    int fps = 0;
    int once = 0;
    float angle = 1;
    float ro = 5;
    while (!quit)
    {
        params->cam->pos[0] = ro*cos(angle);
        params->cam->pos[2] = ro*sin(angle);
        params->cam->yaw = angle;
        angle+=.03;
        render_screen(params->rcp);
        SDL_UnlockTexture(params->texture);
        SDL_RenderCopy(params->renderer, params->texture, NULL, NULL); 
        SDL_RenderPresent(params->renderer);
        fps++;
        if(last != time(NULL)){
            printf("%i fps\n", fps);
            fps = 0;
            last = time(NULL);
        }
        if(SDL_PollEvent(&event))
        {
            if(event.type == SDL_QUIT || once)
            {
                quit = 1;
            }
        }
    }
    return 0;
}


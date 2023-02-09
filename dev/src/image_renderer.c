#include "../include/image_renderer.h"
#define DIV_IMG_THREAD 100

int setup_window(app_params* params){
    omp_set_num_threads(omp_get_num_procs());
    SDL_Init(SDL_INIT_VIDEO);
    params->window = SDL_CreateWindow("SDL2 Displaying Image",
            SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
            params->width, params->height ,0);
    params->renderer = SDL_CreateRenderer(params->window, -1, SDL_RENDERER_ACCELERATED);
    return 0;
}

void degrade(Uint32* pixels, int width, int height)
{
    SDL_PixelFormat *format;
    size_t i;
    format = SDL_AllocFormat(SDL_PIXELFORMAT_RGB888);
    srand(time(NULL));
    int g = rand()%255;
    int b = rand()%255;
    #pragma omp parallel for
    for(i = 0; i < width*height; i++){
        pixels[i] = SDL_MapRGB(format, i%width*(i/width)%255, g, b);
    }
    SDL_FreeFormat(format);
}


int render_camera(app_params* params){
    int quit = 0;
    SDL_Event event;
    time_t last = time(NULL);
    int fps = 0;
    SDL_Texture* texture = SDL_CreateTexture(params->renderer, SDL_PIXELFORMAT_RGB888, SDL_TEXTUREACCESS_STREAMING, params->width, params->height);
    int pitch;
    Uint32* pixels = malloc(sizeof(Uint32)*params->height*params->width);
    SDL_LockTexture(texture, NULL, (void**)&pixels, &pitch);
    while (!quit)
    {
        SDL_RenderClear(params->renderer);
        degrade(pixels, params->width, params->height); 
        SDL_UnlockTexture(texture);
        SDL_RenderCopy(params->renderer, texture, NULL, NULL); 
        SDL_RenderPresent(params->renderer);
        fps++;
        if(last != time(NULL)){
            printf("%i fps\n", fps);
            fps = 0;
            last = time(NULL);
        }
        if(SDL_PollEvent(&event))
        {
            if(event.type == SDL_QUIT)
            {
                free(texture);
                //SDL_DestroyRenderer(params->renderer); 
                SDL_DestroyWindow(params->window);
                SDL_Quit();
                return 0;
            }
        }
    }
    return 0;
}



#include "../include/image_renderer.h"
#define DIV_IMG_THREAD 100

int setup_renderer(app_params* params){

    SDL_Init(SDL_INIT_VIDEO);
    params->window = SDL_CreateWindow("SDL2 Displaying Image",
            SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
            params->width, params->height ,0);
    params->renderer = SDL_CreateRenderer(params->window, -1, SDL_RENDERER_ACCELERATED);
    return 0;
}

void degrade(SDL_Texture* texture, SDL_Renderer *renderer, int width, int height)
{
    SDL_PixelFormat *format;
    Uint32* pixels = malloc(sizeof(Uint32)*height*width);
    size_t i;
    int pitch;
    SDL_LockTexture(texture, NULL, (void**)&pixels, &pitch);
    printf("Lock\n");
    format = SDL_AllocFormat(SDL_PIXELFORMAT_RGBA8888);
    for(i = 0; i < width*height; i++)
        pixels[i] = SDL_MapRGBA(format, i%255, 0, 0, 255);
    SDL_UnlockTexture(texture);
    SDL_FreeFormat(format);
}


int launch(app_params* params){ 
    int quit = 0;
    SDL_Event event;
    time_t last = time(NULL);
    int fps = 0;
    SDL_Rect rect;
    rect.x = 0;
    rect.y = 0;
    rect.w = params->width;
    rect.h = params->height;
    SDL_Texture* texture = SDL_CreateTexture(params->renderer, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_STREAMING, params->width, params->height);
    while (!quit)
    {
        if(SDL_PollEvent(&event))
        {
            if(event.type == SDL_QUIT)
            {
                quit = 1;
                break;
            }
        }
        SDL_RenderClear(params->renderer);
        degrade(texture, params->renderer, params->width, params->height); 
        SDL_RenderCopy(params->renderer, texture, &rect, &rect); 
        free(texture);
        SDL_RenderPresent(params->renderer);
        fps++;
        if(last != time(NULL)){
            printf("%i fps\n", fps);
            fps = 0;
            last = time(NULL);
        }
    }
    SDL_DestroyRenderer(params->renderer); 
    SDL_DestroyWindow(params->window);
    SDL_Quit();
    return 0;
}


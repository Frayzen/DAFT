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

size_t min(size_t i, size_t j){
    return i < j ? i : j;
}
void render(SDL_Surface* surface, size_t width, size_t height){
    //RENDERING PIXEL BY PIXEL PART
    size_t subw = width/DIV_IMG_THREAD; 
    size_t subh = height/DIV_IMG_THREAD;

    pthread_t tids[subh][subw];
    thread_info* ti = malloc(sizeof(thread_info));
    ti->surface = surface;
    for(size_t ix = 0; ix < subw; ix++){
        for(size_t iy = 0; iy < subh; iy++){
            ti->xs = ix*DIV_IMG_THREAD;
            ti->ys = iy*DIV_IMG_THREAD;
            ti->xe = min(width-1, (ix+1)*DIV_IMG_THREAD);
            ti->ye = min(height-1, (iy+1)*DIV_IMG_THREAD);

            pthread_create(&(tids[iy][ix]), NULL, render_pixel, ti);
        }
    }
    void** retval = malloc(sizeof(void*));
    for(size_t ix = 0; ix < subw; ix++){
        for(size_t iy = 0; iy < subh; iy++){
            int err = pthread_join(tids[iy][ix], retval);
            if(err)
                errx(3, "An error occured during image thread processing (id:%i)\n", err);
        }
    }
    free(retval);
    free(ti);
}

void set_pixel(SDL_Surface *surface, size_t x, size_t y, Uint32 pixel)
{
    Uint32 * const target_pixel = (Uint32 *) ((Uint8 *) surface->pixels
            + y * surface->pitch
            + x * surface->format->BytesPerPixel);
    *target_pixel = pixel;
}

void* render_pixel(void* tiv){
    thread_info* ti = tiv;
    for(size_t x = ti->xs; x < ti->xe; x++){
        for(size_t y = ti->ys; y < ti->ye; y++)
            set_pixel(ti->surface, x, y, SDL_MapRGB(ti->surface->format, 255, 0, 0));
    }
    pthread_exit(NULL);
}

int launch(app_params* params){ 
    int quit = 0;
    SDL_Event event;
    SDL_Surface* surface = SDL_GetWindowSurface(params->window); 
    while (!quit)
    {
        SDL_WaitEvent(&event);
        switch (event.type)
        {
            case SDL_QUIT:
                quit = 1;
                break;

            case SDL_WINDOWEVENT:
                render(surface, params->width, params->height);
                SDL_UpdateWindowSurface(params->window);
                break;
        }
    }
    SDL_UnlockSurface(surface);
    SDL_DestroyRenderer(params->renderer); 
    SDL_DestroyWindow(params->window);
    SDL_Quit();
    return 0;
}


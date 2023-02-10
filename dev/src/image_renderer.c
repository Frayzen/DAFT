#include "../include/image_renderer.h"
#include "../include/raycast.h"
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

void render(Uint32* pixels, int width, int height, camera* cam, world* w)
{
    SDL_PixelFormat *format;
    size_t i;
    format = SDL_AllocFormat(SDL_PIXELFORMAT_RGB888);
    raycast_param rcp;
    rcp.width = width;
    rcp.height = height;
    rcp.wd = w;
    rcp.cam = cam;
    //    #pragma omp parallel for private(rcp)
    for(i = 0; i < width*height; i++){
        rcp.x_pix = i%width;
        rcp.y_pix = i/width;
        int r = ray_cast_pixel(rcp);
        pixels[i] = SDL_MapRGB(format, r,r,r);
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
    int once = 0;
    float angle = 0;
    float ro = 4;
    while (!quit)
    {
        SDL_RenderClear(params->renderer);
        render(pixels, params->width, params->height, params->cam, params->wd);
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
                SDL_DestroyTexture(texture);
                SDL_Quit();
                free(pixels);
                return 0;
            }
        }
        if(once){
            free(texture);
            //SDL_DestroyRenderer(params->renderer); 
            SDL_DestroyWindow(params->window);
            SDL_DestroyTexture(texture);
            SDL_Quit();
            free(pixels);
            return 0;
        }
        params->cam->pos = npoint(ro*cos(angle), 0, ro*sin(angle));
        params->cam->yaw = M_PI + angle;
        angle+=.1;
    }
    SDL_DestroyTexture(texture);
    free(pixels);
    return 0;
}



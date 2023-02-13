#include "../include/image_renderer.h"
#include "../include/raycast.h"
#define DIV_IMG_THREAD 100

int setup_window(app_params* params){
    omp_set_num_threads(omp_get_num_procs());
    SDL_Init(SDL_INIT_VIDEO);
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
    return 0;
}
void render_adaptative(ray* r, ray* rays, size_t x, size_t y, size_t width, size_t height){
   if(x != 0){
       ray src = rays[x-1+y*width];
       printf("HEY %p\n", src.m->vertexes);
       printf("LENGTH %lu FOR ID %lu\n", src.m->v_size, src.tri->vert[0]);
       ray_intersect(src.tri, src.m, r);
       if(r->hit)
           return;
   }
}
void render(Uint32* pixels, int width, int height, camera* cam, world* w)
{
    SDL_PixelFormat *format;
    size_t i;
    format = SDL_AllocFormat(SDL_PIXELFORMAT_ARGB8888);
    ray* rays = calloc(sizeof(ray), width*height);
    for(i = 0; i < width*height; i+=2){
        if(i%width == 1)
            i--;
        else if(i%width == 0)
            i++;
        raycast_param rcp;
        rcp.width = width;
        rcp.height = height;
        rcp.wd = w;
        rcp.cam = cam;
        rcp.x_pix = i%width;
        rcp.y_pix = i/width;
        rays[i] = ray_cast_pixel(rcp);
        pixels[i] = SDL_MapRGB(format, rays[i].hit,rays[i].hit,rays[i].hit);
    }
    for(i = 1; i < width*height; i+=2){
        if(i%width == 1)
            i--;
        else if(i%width == 0)
            i++;
        size_t x = i%width;
        size_t y = i/width;
        ray r = nray(cam, x, y, width, height);
        render_adaptative(&r, rays, x, y, width, height);
        pixels[i] = SDL_MapRGB(format, rays[i].hit,rays[i].hit,rays[i].hit);
    }
    SDL_FreeFormat(format);
    free(rays);
}


int render_camera(app_params* params){
    int quit = 0;
    SDL_Event event;
    time_t last = time(NULL);
    int fps = 0;
    SDL_Texture* texture = SDL_CreateTexture(params->renderer, SDL_PIXELFORMAT_ARGB8888, SDL_TEXTUREACCESS_STREAMING, params->width, params->height);
    int pitch;
    Uint32* pixels = malloc(sizeof(Uint32)*params->height*params->width);
    Uint32* locked_pixels = NULL;
    int once = 0;
    float angle = 0;
    float ro = 4;
    while (!quit)
    {
        SDL_RenderClear(params->renderer);
        render(pixels, params->width, params->height, params->cam, params->wd);
        SDL_LockTexture(texture, NULL, (void**)&locked_pixels, &pitch);
        memcpy(locked_pixels, pixels, sizeof(Uint32)*params->height*params->width);
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



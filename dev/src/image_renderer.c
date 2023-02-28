#include "../include/image_renderer.h"
#include "../include/raycast.h"
#define DIV_IMG_THREAD 100

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
    return 0;
}
void cover_surface(size_t fromx, size_t tox, size_t fromy, size_t toy, size_t width, size_t height, size_t size, camera* cam, world* w, ray* rays){
    if(size < 1)
        return;
    size_t i, j;
    #pragma omp parallel for
    for(j = fromy; j < toy; j+=size)
    #pragma omp parallel for
    for(i = fromx; i < tox; i+=size){
        size_t k = j*width+i;
        if(rays[k].hit)
            continue;
        size_t x_pix = i;
        size_t y_pix = j;
        ray r;
        if(!rays[k].hit)
            r = ray_cast_pixel(cam, w, x_pix, y_pix, width, height);
        else
            r = rays[k];
        rays[k] = r;
        if(r.hit)
            ray_cast_neighbour(w, cam, i, j, width, height, rays, k);
        //printf("COLORS %i %i %i\n", c.r, c.g, c.b);
    }
     
}
void render(Uint32* pixels, int width, int height, camera* cam, world* w)
{
    SDL_PixelFormat *format;
    format = SDL_AllocFormat(SDL_PIXELFORMAT_RGBA8888);
    ray *rays = calloc(sizeof(ray), height*width);
    int size = 8;
    cover_surface(0,width,0,height,width,height, size, cam ,w ,rays);
    #pragma omp parallel for
    for(size_t i = 0; i < width*height; i++){
        ray r = rays[i];
        color c = r.c;
        pixels[i] = SDL_MapRGB(format, c.r,c.g,c.b);
    }
    SDL_FreeFormat(format);
    free(rays);
}


int render_camera(app_params* params){
    int quit = 0;
    SDL_Event event;
    time_t last = time(NULL);
    int fps = 0;
    SDL_Texture* texture = SDL_CreateTexture(params->renderer, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_STREAMING, params->width, params->height);
    int pitch;
    Uint32* pixels;;
    int once = 0;
    float angle = 0;
    float ro = 4;
    SDL_Surface* old = params->cam->skybox;
    params->cam->skybox = SDL_ConvertSurfaceFormat(old, SDL_PIXELFORMAT_RGBA8888, 0);
    SDL_FreeSurface(old);
    SDL_LockTexture(texture, NULL, (void**)&pixels, &pitch);
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
        angle+=.03;
    }
    SDL_DestroyTexture(texture);
    free(pixels);
    return 0;
}



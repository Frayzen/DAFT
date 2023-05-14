#include "../../include/window/renderer.h"

int percentage = 0;
pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;

void render_screen(rendering_params* rdp)
{
    //pixels = wodth*height-1
    Uint32* pixels = rdp->pixels;
    memset(pixels, 0, rdp->width*rdp->height*sizeof(Uint32));
    int width = rdp->width;
    int height = rdp->height;
    SDL_PixelFormat* format = rdp->format;
        
    update_cam_sides(rdp);
    int* pixels_rasterize = calloc(sizeof(int)*width*height, 1);
    #if USE_RASTERIZE
    render_rasterize(rdp, pixels_rasterize);
    #else
    memset(pixels_rasterize, 1, width*height);
    #endif

    #pragma omp parallel for
    for(int i = 0; i < width*height; i++){
        ray r = create_ray_interpolate(rdp, i%width, i/width);
        raycast_param* rcp = init_raycast_param(&r, rdp->w, rdp->reflection, rdp->shadow, 0);
        rcp->show_lights = 1;
        if(pixels_rasterize[i] == 2){
                pixels[i] = SDL_MapRGBA(format, 255, 0, 0, 255);
        }else{
            rcp->compute_meshes = pixels_rasterize[i];
            ray_cast(rcp);

            if(r.last_hit != NULL){
                pixels[i] = SDL_MapRGBA(format, r.last_hit->color[0]*255, r.last_hit->color[1]*255, r.last_hit->color[2]*255, 255);
                free(r.last_hit);
            }
        }
    }
    free(pixels_rasterize);


    int ppixels = (percentage*width*height)/100;

    if(percentage < 100 && percentage > 0){
        for (int w = 0; w < width; w++)
        {
            for (int h = 0; h < height/20; h++)
            {
                if (w*h >= ppixels)
                    break;
                else
                {
                    if (w < percentage*width/100)
                        pixels[h*width+w] = SDL_MapRGBA(format, 0, 255, 0, 255);
                    else
                        pixels[h*width+w] = SDL_MapRGBA(format, 0, 0, 0, 0);
                }
            }
        }
    }
}

void set_pixel(SDL_Surface *surface, int x, int y, Uint32 color)
{
    int bpp = surface->format->BytesPerPixel;
    Uint8 *p = (Uint8 *)surface->pixels + y * surface->pitch + x * bpp;
     
    if(bpp == 1)
        *p = color;
    else if(bpp == 2)
        *(Uint16*)p = color;
    else if(bpp == 4)
        *(Uint32*)p = color;
    else
    {
        if(SDL_BYTEORDER == SDL_BIG_ENDIAN)
        {
            p[0] = (color >> 16) & 0xff;
            p[1] = (color >> 8) & 0xff;
            p[2] = color & 0xff;
        }
        else
        {
            p[0] = color & 0xff;
            p[1] = (color >> 8) & 0xff;
            p[2] = (color >> 16) & 0xff;
        }
    }
}

// responsible for freeing the raycast_params struct and the image
void* render_quality_process(void* rdpptr){
    rendering_params* rdp = (rendering_params*)rdpptr;
    SDL_Surface* image = SDL_CreateRGBSurface(0, rdp->width, rdp->height, 32, 0, 0, 0, 0);
    
    int width = rdp->width;
    int height = rdp->height;
    SDL_PixelFormat* format = image->format;
    world* w = rdp->w;
    update_cam_sides(rdp);
    for(int i = 0; i < width*height; i++){
        ray r = create_ray_interpolate(rdp, i%width, i/width);
        raycast_param* rcp = init_raycast_param(&r, w, 1, 1, 1);
        ray_cast(rcp);
        if(r.last_hit != NULL){
            set_pixel(image, i%width, i/width, SDL_MapRGBA(format, r.last_hit->color[0]*255, r.last_hit->color[1]*255, r.last_hit->color[2]*255, 255));
            free(r.last_hit);
        }
        else
            set_pixel(image, i%width, i/width, SDL_MapRGBA(format, 0, 0, 0, 255));
        if(i%100 == 0){
            pthread_mutex_lock(&mutex);
            percentage = 100*i/(width*height);
            pthread_mutex_unlock(&mutex);
        }
    }
    pthread_mutex_lock(&mutex);
    percentage = 0;
    pthread_mutex_unlock(&mutex);


    SDL_SaveBMP(image, "out.png");
    printf("END OF COPY !\n");
    SDL_FreeSurface(image);
    free(rdp->cam);
    free_rendering_params(rdp);
    return NULL;
}

void render_quality(rendering_params* rdp){
    if(percentage != 0)
        return;
    printf("RENDERING...\n");
    pthread_t thread;
    pthread_create(&thread, NULL, render_quality_process, (void*)rdp);
}

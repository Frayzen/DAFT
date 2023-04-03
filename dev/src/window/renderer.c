#include "../../include/window/renderer.h"

void render_screen(raycast_params* rcp)
{
    Uint32* pixels = rcp->pixels;
    int width = rcp->width;
    int height = rcp->height;
    SDL_PixelFormat* format = rcp->format;
    struct world* w = rcp->w;
    update_sides(rcp);
    #pragma omp parallel for
    for(int i = 0; i < width*height; i++){
        ray r = create_ray_interpolate(rcp, i%width, i/width);
        ray_cast(&r, w, 1);
        if(r.last_hit != NULL){
            pixels[i] = SDL_MapRGBA(format, r.last_hit->color[0]*255, r.last_hit->color[1]*255, r.last_hit->color[2]*255, 255);
            free(r.last_hit);
        }
        else
            pixels[i] = SDL_MapRGBA(format, 0, 0, 0, 255);
    }
}

void setPixel(SDL_Surface *surface, int x, int y, Uint32 color)
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
void* render_quality_process(void* rcpptr){
    raycast_params* rcp = (raycast_params*)rcpptr;
    SDL_Surface* image = SDL_CreateRGBSurface(0, rcp->width, rcp->height, 32, 0, 0, 0, 0);
    
    int width = rcp->width;
    int height = rcp->height;
    SDL_PixelFormat* format = image->format;
    world* w = rcp->w;
    update_sides(rcp);
    for(int i = 0; i < width*height; i++){
        ray r = create_ray_interpolate(rcp, i%width, i/width);
        ray_cast(&r, w, 0);
        if(r.last_hit != NULL){
            setPixel(image, i%width, i/width, SDL_MapRGBA(format, r.last_hit->color[0]*255, r.last_hit->color[1]*255, r.last_hit->color[2]*255, 255));
            free(r.last_hit);
        }
        else
            setPixel(image, i%width, i/width, SDL_MapRGBA(format, 0, 0, 0, 255));
        if(i%100000 == 0){
            printf("%f%%\n", (float)i/(width*height)*100);
        }
    }


    SDL_SaveBMP(image, "out.png");
    printf("END OF COPY !\n");
    SDL_FreeSurface(image);
    free(rcp->cam);
    free_raycast_params(rcp);
    return NULL;
}

void render_quality(raycast_params* rcp){
    pthread_t thread;
    pthread_create(&thread, NULL, render_quality_process, (void*)rcp);
}

#include "../../include/window/renderer.h"

void render_screen(raycast_params* rcp)
{
    update_sides(rcp);
    rays[0].last_hit = calloc(sizeof(ray_result), 1);
    #pragma omp parallel for
    for(int i = 0; i < width*height; i++){
        ray r = create_ray_interpolate(rdr);
        ray_cast(&r, w);
        pixels[i] = SDL_MapRGBA(format, 255, 255, 255, 0);
    }
    free_corners(rcp);
    SDL_FreeFormat(format);
}
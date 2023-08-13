#include "../../include/physic/shadow.h"

// formula is
//  c = ka * Ia + kd * Id * (N dot L) + ks * Is * (R dot V)^n
//  c = color
//  ka = ambient coef
//  Ia = ambient c
//  kd = diffuse coef
//  Id = diffuse c
//  ks = specular coef
//  Is = specular c
//  N = normal
//  L = c direction
//  R = reflection vector
//  V = view vector
//  n = shininess

// if n dot L < 0 then n dot L = 0

// c = ka + sum cl * [kd * n dot L + ks * (h dot dhi)^s]
//  c is the color of the pixel
//  ka is the color of the object
//  cl is color of the light
//  kd is the material difuse coef
//  n is the normal
//  L is the c direction

void get_pixel_color(SDL_Surface *surface, int x, int y, Uint8 *r, Uint8 *g, Uint8 *b)
{
    Uint32 pixel = *((Uint32 *)surface->pixels + y * surface->w + x);
    SDL_GetRGB(pixel, surface->format, r, g, b);
}

void get_color_at(ray *ry, SDL_Surface *text, float3 color)
{
    mesh *m = ry->last_hit->m;
    float3 uvw = ry->last_hit->uvw;
    int tri = ry->last_hit->tri;
    float2 pts[3];
    get_vt_from_tri(m, tri, pts);
    float x = (pts[0].x * uvw.z + pts[1].x * uvw.x + pts[2].x * uvw.y);
    float y = (pts[0].y * uvw.z + pts[1].y * uvw.x + pts[2].x * uvw.y);
    int px = (int)(x * text->w);
    int py = (int)((1 - y) * text->h);
    Uint8 r, g, b;
    get_pixel_color(text, px, py, &r, &g, &b);
    color.x = r / 255.0;
    color.y = g / 255.0;
    color.z = b / 255.0;
}

void clamp_vect(float3* color)
{
    // clamp between 0 and 1
    color->x = color->x > 1 ? 1 : color->x;
    color->y = color->y > 1 ? 1 : color->y;
    color->z = color->z > 1 ? 1 : color->z;
    color->x = color->x < 0 ? 0 : color->x;
    color->y = color->y < 0 ? 0 : color->y;
    color->z = color->z < 0 ? 0 : color->z;
}

void shadow_render(raycast_param *rcp)
{
    if (rcp->shadow == 0)
        return;
    ray *ry = rcp->r;
    material *mat = ry->last_hit->mat;
    if(mat == NULL)
        return;
    world *w = rcp->w;

    // setup
    ray *shadow_ray = calloc(sizeof(struct ray), 1);
    float3 difuse = {0, 0, 0};
    float3 specular = {0, 0, 0};

    // position of the shadow ray
    copy(ry->last_hit->normal, shadow_ray->pos);
    scale(shadow_ray->pos, .001, shadow_ray->pos);
    add(shadow_ray->pos, ry->last_hit->pos, shadow_ray->pos);

    for (int i = 0; i < w->size_lights; i++)
    {
        // shadow ray direction
        light *lgt = w->lights[i];
        float3 dist;
        minus(lgt->pos, shadow_ray->pos, dist);
        shadow_ray->dir = normalize(dist);
        shadow_ray->last_hit = calloc(sizeof(ray_result), 1);

        // setup mint
        float mint = norm(dist);
        shadow_ray->last_hit->mint = mint;
        // raycast
        ray_cast(init_raycast_param(shadow_ray, w, 0, 0, 0));
        if (shadow_ray->last_hit->mint == mint)
        {
            // diffuse
            float dp = max(0, dotProduct(shadow_ray->dir, ry->last_hit->normal));
            float3 lgt_difs = {dp, dp, dp};
            scale_vector(mat->diffuse, lgt_difs, lgt_difs);
            if (mat->diffuseText != NULL)
            {
                float3 difTextCol = {0, 0, 0};
                get_color_at(ry, mat->diffuseText, difTextCol);
                scale_vector(difTextCol, lgt_difs, lgt_difs);
            }
            scale_vector(lgt->color, lgt_difs, lgt_difs);
            add(lgt_difs, difuse, difuse);

            // specular
            float3 r_m;
            copy(ry->last_hit->normal, r_m);
            scale(r_m, (2 * dp), r_m);
            minus(r_m, shadow_ray->dir, r_m);

            float3 to_view;
            scale(ry->dir, -1, to_view);
            to_view = normalize(to_view);

            dp = max(0, dotProduct(to_view, r_m));
            dp = pow(dp, mat->shininess);
            float3 lgt_spec = {dp, dp, dp};
            scale_vector(mat->specular, lgt_spec, lgt_spec);
            if (mat->specularText != NULL)
            {
                float3 specTextCol = {0, 0, 0};
                get_color_at(ry, mat->specularText, lgt_spec);
                scale_vector(specTextCol, lgt_spec, lgt_spec);
            }
            scale_vector(lgt->color, lgt_spec, lgt_spec);
            add(lgt_spec, specular, specular);
        }
    }
    float3 ambient = {1, 1, 1};
    scale_vector(mat->ambient, ambient, ambient);
    if (mat->ambientText != NULL)
    {
        float3 ambTextCol = {0, 0, 0};
        get_color_at(ry, mat->ambientText, ambTextCol);
        scale_vector(ambTextCol, ambient, ambient);
    }

    // difuse  = difuse * (1 - ambient)
    float3 factor = {1, 1, 1};
    minus(factor, ambient, factor);
    scale_vector(difuse, factor, difuse);
    add(ambient, difuse, difuse);
    scale_vector(difuse, ry->last_hit->color, ry->last_hit->color);
    // add specular
    add(ry->last_hit->color, specular, ry->last_hit->color);
    clamp_vect(&ry->last_hit->color);

    free(shadow_ray);
}
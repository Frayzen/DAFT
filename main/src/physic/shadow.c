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

void get_color_at(ray *ry, SDL_Surface *text, float *color)
{
    mesh *m = ry->last_hit->m;
    float *uvw = ry->last_hit->uvw;
    triangle *tri = ry->last_hit->tri;
    float *pt0 = m->texture_vertices[tri->vt[0]];
    float *pt1 = m->texture_vertices[tri->vt[1]];
    float *pt2 = m->texture_vertices[tri->vt[2]];
    float x = (pt0[0] * uvw[2] + pt1[0] * uvw[0] + pt2[0] * uvw[1]);
    float y = (pt0[1] * uvw[2] + pt1[1] * uvw[0] + pt2[1] * uvw[1]);
    int px = (int)(x * text->w);
    int py = (int)((1 - y) * text->h);
    Uint8 r, g, b;
    get_pixel_color(text, px, py, &r, &g, &b);
    color[0] = r / 255.0;
    color[1] = g / 255.0;
    color[2] = b / 255.0;
}

void clamp(float *color)
{
    for (int i = 0; i < 3; i++)
    {
        if (color[i] > 1)
            color[i] = 1;
        if (color[i] < 0)
            color[i] = 0;
    }
}

void shadow_render(raycast_param *rcp)
{
    if (rcp->shadow == 0)
        return;
    ray *ry = rcp->r;
    material *mat = ry->last_hit->mat;
    world *w = rcp->w;

    // setup
    ray *shadow_ray = calloc(sizeof(struct ray), 1);
    float difuse[3] = {0, 0, 0};
    float specular[3] = {0, 0, 0};

    // position of the shadow ray
    copy(ry->last_hit->normal, shadow_ray->pos);
    scale(shadow_ray->pos, .001, shadow_ray->pos);
    add(shadow_ray->pos, ry->last_hit->pos, shadow_ray->pos);

    for (int i = 0; i < w->size_lights; i++)
    {
        // shadow ray direction
        light *lgt = w->lights[i];
        float dist[3];
        minus(lgt->pos, shadow_ray->pos, dist);
        normalize(dist, shadow_ray->dir);
        shadow_ray->last_hit = calloc(sizeof(ray_result), 1);

        // setup mint
        float mint = norm(dist);
        shadow_ray->last_hit->mint = mint;
        // raycast
        ray_cast(init_raycast_param(shadow_ray, w, 0, 0, 0, 0));
        if (shadow_ray->last_hit->mint == mint)
        {
            // diffuse
            float dp = max(0, dotProduct(shadow_ray->dir, ry->last_hit->normal));
            if (rcp->shadow_mask & MASK_DIFFUSE)
            {
                float lgt_difs[3] = {dp, dp, dp};
                scale_vector(mat->diffuse, lgt_difs, lgt_difs);
                if (mat->diffuseText != NULL)
                {
                    float difTextCol[3] = {0, 0, 0};
                    get_color_at(ry, mat->diffuseText, difTextCol);
                    scale_vector(difTextCol, lgt_difs, lgt_difs);
                }
                scale_vector(lgt->color, lgt_difs, lgt_difs);
                add(lgt_difs, difuse, difuse);
            }
            if (rcp->shadow_mask & MASK_SPECULAR)
            {
                // specular
                float r_m[3];
                copy(ry->last_hit->normal, r_m);
                scale(r_m, (2 * dp), r_m);
                minus(r_m, shadow_ray->dir, r_m);

                float to_view[3];
                scale(ry->dir, -1, to_view);
                normalize(to_view, to_view);

                dp = max(0, dotProduct(to_view, r_m));
                dp = pow(dp, mat->shininess);
                float lgt_spec[3] = {dp, dp, dp};
                scale_vector(mat->specular, lgt_spec, lgt_spec);
                if (mat->specularText != NULL)
                {
                    float specTextCol[3] = {0, 0, 0};
                    get_color_at(ry, mat->specularText, lgt_spec);
                    scale_vector(specTextCol, lgt_spec, lgt_spec);
                }
                scale_vector(lgt->color, lgt_spec, lgt_spec);
                add(lgt_spec, specular, specular);
            }
        }
    }
    float ambient[3] = {1, 1, 1};
    scale_vector(mat->ambient, ambient, ambient);
    if (mat->ambientText != NULL)
    {
        float ambTextCol[3] = {0, 0, 0};
        get_color_at(ry, mat->ambientText, ambTextCol);
        scale_vector(ambTextCol, ambient, ambient);
    }

    // difuse  = difuse * (1 - ambient)
    float factor[3] = {1, 1, 1};
    minus(factor, ambient, factor);
    scale_vector(difuse, factor, difuse);
    add(ambient, difuse, difuse);
    scale_vector(difuse, ry->last_hit->color, ry->last_hit->color);
    // add specular
    if (rcp->shadow_mask & MASK_SPECULAR)
    {
        add(ry->last_hit->color, specular, ry->last_hit->color);
    }
    clamp(ry->last_hit->color);

    free(shadow_ray);
}
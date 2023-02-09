#include "../include/raycast.h"

/*
double dotProduct(Vector a, Vector b) {
    return a.x * b.x + a.y * b.y + a.z * b.z;
}
//returns 0 : the ray and plane are almost parallel
//
//returns 1 : we have detected the intersection, its coordinates are stored in
//           intersetion parameter
int intersectionRayPlane(Ray ray, Plane plane, point *intersection) {
    
    //check if plane and ray are parallel
    double d = dotProduct(plane.normal, ray.direction);
    if (fabs(d) < 1e-6) {
        return 0;
    }
    double t = -(dotProduct(plane.normal, ray.origin) + plane.d) / d;
    if (t < 0) {
        return 0;
    }
    intersection->x = ray.origin.x + t * ray.direction.x;
    intersection->y = ray.origin.y + t * ray.direction.y;
    intersection->z = ray.origin.z + t * ray.direction.z;
    return 1;
}
*/
float area_triangle(point * a, point * b, point * c)
{
    point ab = {b->x - a->x, b->y - a->y, b->z - a->z};
    point ac = {c->x - a->x, c->y - a->y, c->z - a->z};
    point * cross = init_point(0, 0, 0, 0);
    crossProduct(&ab, &ac, cross);
    float area = 0.5 * sqrtf(dot(cross, cross));
    free(cross);
    return area;

}

void ray_intersect(ray * ray, point * vertex, point * normal)
{

    float d = dot(normal, vertex);
    float n_p = dot(normal, &ray->pos);
    float n_rd = dot(normal, &ray->dir);
    //printf("d = %f\n" , d);
    //printf("n_p = %f\n" , n_p);
    //printf("n_rd = %f\n" , n_rd);
    float t = (d - n_p)/n_rd;
    //printf("t: %f\n", t);
    if(t > 0)
    {

        point  p = {0, ray->pos.x + t*ray->dir.x, ray->pos.y + t*ray->dir.y, ray->pos.z + t*ray->dir.z};

        ray->contact = p;
        ray->hit = -1;

    }
    else
    {
        ray->hit = 0;
    }


}


void hit_triangle(ray * ray, mesh * mesh, size_t index)
{

    point * a = mesh->vertexes[mesh->triangles[index]->vert[0]];
    point * b = mesh->vertexes[mesh->triangles[index]->vert[1]];
    point * c = mesh->vertexes[mesh->triangles[index]->vert[2]];
    minus(a,c);
    ray_intersect(ray, a, &mesh->triangles[index]->normal);
    if (ray->hit == -1) {
        point *p = &ray->contact;
        if (area_triangle(a, b, c) == area_triangle(p, a, b) + area_triangle(p, b, c) + area_triangle(p, c, a)) {
            ray->hit = 1;
        }
    }

}

int ray_cast_pixel(raycast_param params){
    float yaw = params.cam->yaw;
    float pitch = params.cam->pitch;
    float FOV = params.cam->FOV;
    float pitch_ratio = 1-2*params.x_pix/params.width;
    float yaw_ratio = 1-2*params.y_pix/params.height;
    float cur_yaw = yaw+yaw_ratio*FOV;
    float cur_pitch = pitch+pitch_ratio*FOV;
    point dir = npoint(cos(cur_pitch)*sin(cur_yaw),sin(cur_pitch),cos(cur_pitch)*cos(cur_yaw));
    ray* ry = init_ray(0, params.cam->pos, dir);
    world* wd = params.wd;
    for(size_t id_mesh = 0; id_mesh < wd->size_m; id_mesh++){
        mesh* m = wd->meshes[id_mesh];
        for(size_t t_id = 0; t_id < m->t_size; t_id++){
            //printf("running for the ray ry %f %f %f\n", ry->dir.x, ry->dir.y, ry->dir.z);
            hit_triangle(ry, m, t_id);
            if(ry->hit)
                return 255;
        }
    }
    return 0;
}





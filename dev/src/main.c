#include "image_renderer.c"
#include "utils.c"
#include <stdio.h>

int main(){
    mesh * m = init_mesh(3, 1, 0);
    add_vertex(m, 0, 0, 0, -10);
    add_vertex(m, 0, -20, 0, -10);
    add_vertex(m, 0, 0, -20, -10);
    add_tri(m, 0, 0,1, 2);
    m->triangles[0]->normal = *init_point(0, 0, 0, 1);


    ray * r = init_ray(0, *init_point(0, 10, 10, 10),
                       *init_point(0, 0, 0, 1));


    //ray_intersect(r, m->vertexes[m->triangles[0]->vert[0]], &m->triangles[0]->normal, m);

    int x =
    printf("ray pos = %f, %f, %f\n", r->pos.x, r->pos.y, r->pos.z);



    printf("Hit point : %f %f %f\n", r->pos.x, r->pos.y, r->pos.z);
    return 0;
}

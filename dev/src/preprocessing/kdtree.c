
#include <stdlib.h>
#include "../../include/architecture/kdtree.h"

triangle * sort_triangles(triangle * tris, int nb_tris, int axis, mesh * m)
{
    float values[nb_tris];
    for (int i = 0; i < nb_tris; i++)
    {
        values[i] = get_middle(tris[i], m)[axis];
    }
    for (int i = 0; i < nb_tris; i++)
    {
        for (int j = i + 1; j < nb_tris; j++)
        {
            if (values[i] > values[j])
            {
                float tmp = values[i];
                values[i] = values[j];
                values[j] = tmp;
                triangle tmp2 = tris[i];
                tris[i] = tris[j];
                tris[j] = tmp2;

            }
        }
    }
    return tris;
}

kdtree * kdtree_create(triangle *triangles, int nb_triangles, int depth, mesh * m)
{
    if (nb_triangles <= MINTRIANGLES)
    {
        kdtree * node  = malloc(sizeof(kdtree));
        node->axis = -1;
        node->nb_triangles = nb_triangles;
        node->triangles = triangles;
        node->value = 0;
        node->left = NULL;
        node->right = NULL;
        node->box = init_bbox(get_min_points(m), get_max_points(m));
        return node;
    }
    else
    {
        kdtree * node  = malloc(sizeof(kdtree));
        node->axis = depth % 3;
        node->nb_triangles = nb_triangles;
        node->triangles = sort_triangles(triangles, nb_triangles, node->axis, m);
        node->value = get_middle(node->triangles[nb_triangles / 2], m)[node->axis];

        node->left = kdtree_create(node->triangles, nb_triangles / 2, depth + 1, m);
        node->right = kdtree_create(node->triangles + nb_triangles / 2, nb_triangles - nb_triangles / 2, depth + 1, m);
        node->box = init_bbox(node->left->box->min, node->right->box->max);

        return node;
    }

}




kdtree * init_kdtree(mesh * m)
{
    kdtree * kdtree = malloc(sizeof(kdtree));
    kdtree->axis = 0;
    kdtree->nb_triangles = m->nb_triangles;
    kdtree->triangles = sort_triangles(m->triangles, m->nb_triangles, 0, m);
    kdtree->value = get_middle(kdtree->triangles[m->nb_triangles / 2], m)[0];

    kdtree->left = kdtree_create(kdtree->triangles, m->nb_triangles / 2, 1, m);
    kdtree->right = kdtree_create(kdtree->triangles + m->nb_triangles / 2, m->nb_triangles - m->nb_triangles / 2, 1, m);
    kdtree->box = init_bbox(kdtree->left->box->min, kdtree->right->box->max);
    return kdtree;

}


void kdtree_free(kdtree * kdtree)
{
    if (kdtree->axis != -1)
    {
        kdtree_free(kdtree->left);
        kdtree_free(kdtree->right);
    }
    free(kdtree->triangles);
    free(kdtree->box);
    free(kdtree);
}
#include <stddef.h>
#pragma once



typedef struct kdtree {
    int axis;
    float value;
    int nb_triangles;
    triangle *triangles;
    struct kdtree *left;
    struct kdtree *right;
} kdtree;

triangle * sort_triangles(triangle *triangles, int nb_triangles, int axis)
{
    int i, j;
    triangle tmp;
    for (i = 0; i < nb_triangles; i++) {
        for (j = i + 1; j < nb_triangles; j++) {
            if (triangles[i].vertices[axis] > triangles[j].vertices[axis]) {
                tmp = triangles[i];
                triangles[i] = triangles[j];
                triangles[j] = tmp;
            }
        }
    }
    return triangles;
}

kdtree * kdtree_create(triangle *triangles, int nb_triangles, int depth)
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
        return node;
    }
    else
    {
        kdtree * node  = malloc(sizeof(kdtree));
        node->axis = depth % 3;
        node->nb_triangles = nb_triangles;
        node->triangles = sort_triangles(triangles, nb_triangles, node->axis);
        node->value = node->triangles[nb_triangles / 2].vertices[node->axis];
        node->left = kdtree_create(node->triangles, nb_triangles / 2, depth + 1);
        node->right = kdtree_create(node->triangles + nb_triangles / 2, nb_triangles - nb_triangles / 2, depth + 1);
        return node;
    }

}
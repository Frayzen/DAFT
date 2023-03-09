#include "../../include/architecture/mesh.h"
#include


float * get_middle(triangle t, mesh *m)
{
    static float result[3] = {m->vertices[t->vert[0]][0] + m->vertices[t->vert[1]][0] + m->vertices[t->vert[2]][0] /3,
    m->vertices[t->vert[0]][1] + m->vertices[t->vert[1]][1] + m->vertices[t->vert[2]][1] /3,
    m->vertices[t->vert[0]][2] + m->vertices[t->vert[1]][2] + m->vertices[t->vert[2]][2] /3};
    return result;
}

float * get_max_points(mesh *m)
{
    static float res[3] = {m->vertices[0][0], m->vertices[0][1], m->vertices[0][2]};
    for (int i = 1; i < m->nb_vertices; i++)
    {
        if (m->vertices[i][0] > res[0])
        {
            res[0] = m->vertices[i][0];
        }
        if (m->vertices[i][1] > res[1])
        {
            res[1] = m->vertices[i][1];
        }
        if (m->vertices[i][2] > res[2])
        {
            res[2] = m->vertices[i][2];
        }
    }
    return res;
}


float *  get_min_points(mesh *m)
{
    static float res[3] = {m->vertices[0][0], m->vertices[0][1], m->vertices[0][2]};
    for (int i = 1; i < m->nb_vertices; i++)
    {
        if (m->vertices[i][0] < res[0])
        {
            res[0] = m->vertices[i][0];
        }
        if (m->vertices[i][1] < res[1])
        {
            res[1] = m->vertices[i][1];
        }
        if (m->vertices[i][2] < res[2])
        {
            res[2] = m->vertices[i][2];
        }
    }
    return res;
}
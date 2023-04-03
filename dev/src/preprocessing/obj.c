#include "../../include/preprocessing/obj.h"

void parse(char* path, world* w, float scale, float pos[3])
{
    FILE* file;
    file = fopen(path, "r");
    if (file == NULL)
    {
        printf("cant open youre file man\n");
        return;
    }

    size_t vert = 0;
    size_t tri = 0;
    //size_t norm = 0;
    //size_t texture = 0;

    char line[200];

    while (fgets(line, sizeof(line), file) != NULL)
    {
        if (line[0] == 'v')
        {
            if (line[1] == ' ')
                vert++;
        }
        else if (line[0] == 'f')
        {
            int space = 0;
            for (size_t i = 0; line[i] != 0 && line[i] != '\r'; i++)
            {
                if (line[i] == ' ')
                    space++;
            }
            tri = tri + (space-3) +1;
        }
    }

    printf("tri %ld v %ld\n",tri, vert);
    mesh* new_mesh = build_mesh(vert, tri, 0);
    fseek(file, 0, SEEK_SET);

    float v[3];
    while(fgets(line, sizeof(line), file) != NULL)
    {
        if (line[0] == 'v')
        {
            if (line[1] == ' ')
            {
                sscanf(line, "v %f %f %f", &v[0], &v[1], &v[2]);
                scale(v, scale, v);
                add(v, pos, v);
                add_vertex(new_mesh, v);
            }
        }

        if (line[0] == 'f')
        {
            int spc = 0;
            int* p = calloc(3,sizeof(int));
            for (size_t i = 0; line[i] != '\0' && line[i] != '\r'; i ++)
            {
                if (line[i] == ' ')
                {
                    if (spc >= 3)
                    {
                        if (spc == 3)
                            p = realloc(p, sizeof(int)*(spc+1));
                        else
                            p = realloc(p, sizeof(int)*(spc+1));
                    }

                    if (line[i+1] != '\0' && line[i+1] != '\r')
                        p[spc] = atoi(&line[i+1]);
                    spc++;
                }
            }

            for (size_t i = 1; i <= spc-2; i++)
            {
                int points[3];
                points[0] = p[0]-1;
                points[1] = p[i]-1;
                points[2] = p[i+1]-1;
                add_tri(new_mesh, points);
            }
            free(p);

        }
    }
    add_mesh(w, new_mesh);
    fclose(file);
}



#include "../../include/preprocessing/obj_parser.h"

void load_object(char* path, world* w, float scale, float pos[3], char* texture_path, float reflectivity)
{
    FILE* file;
    file = fopen(path, "r");
    if (file == NULL)
    {
        printf("cant open the file named '%s'\n", path);
        return;
    }

    int vert = 0;
    int tri = 0;
    int text_vert = 0;
    //size_t norm = 0;
    //size_t texture = 0;

    char line[200];

    while (fgets(line, sizeof(line), file) != NULL)
    {
        if (line[0] == 'v')
        {
            if (line[1] == ' ')
                vert++;
            if(line[1] == 't')
                text_vert++;
        }
        else if (line[0] == 'f')
        {
            int space = 0;
            for (int i = 0; line[i] != 0 && line[i] != '\r'; i++)
            {
                if (line[i] == ' ')
                    space++;
            }
            tri = tri + (space-3) +1;
        }
    }
    if(vert == 0 || tri == 0){
        printf("The %s file is not a valid obj file\n", path);
        return;
    }
    
    printf("TEXT CVERT %d\n", text_vert);
    mesh* new_mesh = build_mesh(vert, tri, text_vert);
    fseek(file, 0, SEEK_SET);

    float v[3];
    float vt[2];
    while(fgets(line, sizeof(line), file) != NULL)
    {
        if (line[0] == 'v')
        {
            if (line[1] == ' '){
                sscanf(line, "v %f %f %f", &v[0], &v[1], &v[2]);
                scale(v, scale, v);
                add(v, pos, v);
                add_vertex(new_mesh, v);
            }
            if(line[1] == 't'){
                sscanf(line, "v %f %f", &vt[0], &vt[1]);
                add_texture_vertex(new_mesh, vt);
            }
        }

        if (line[0] == 'f' && line[1] == ' ')
        {
            int nb_v;
            // v vt vn
            int* vs[3] = {NULL,NULL,NULL} ;
            int cur_v = 0;
            int cur_nb = 0;
            int i = 2;
            while (line[i] != '\0' && line[i] != '\r')
            {
                    switch (line[i])
                    {
                    case '/':
                        vs[cur_v][nb_v] = cur_nb;
                        cur_v++;
                        cur_nb = 0;
                        break;
                    case ' ':
                        nb_v++;
                        for(int i = 0; i < 3; i++)
                            vs[i] = realloc(v, sizeof(int)*nb_v);
                        cur_nb = 0;
                        cur_v = 0;
                        break;
                    default:
                        int val = atoi(&line[i]);
                        cur_nb*=10;
                        cur_nb+=val;
                        break;
                    }
                }
                i++;

            }

            int v[3];
            int vt[3];
            int vn[3];
            for (int j = 0; j < nb_v-2; j++)
            {
                v[0] = vs[0][j] -1;
                v[1] = vs[0][j+1] -1;
                v[2] = vs[0][j+2] -1;

                vt[0] = vs[1][j];
                vt[0] = vs[1][j+1];
                vt[0] = vs[1][j+2];

                vn[0] = vs[2][j];
                vn[0] = vs[2][j+1];
                vn[0] = vs[2][j+2];
                add_tri(new_mesh, v, vt, vn);
            }
            free(p);

        }
    }
    if(texture_path != NULL){
        load_texture(new_mesh, texture_path);
    }
    printf("Mesh loaded : %s (%d vertices, %d triangles)\n", path, new_mesh->nb_vertices, new_mesh->nb_triangles);
    new_mesh->reflectivity = reflectivity;
    add_mesh(w, new_mesh);
    fclose(file);
}


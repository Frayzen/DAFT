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

        if (line[0] == 'f')
        {
            int spc = 0;
            int* p = calloc(3,sizeof(int));
            for (int i = 0; line[i] != '\0' && line[i] != '\r'; i ++)
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
    if(texture_path != NULL){
        load_texture(new_mesh, texture_path);
    }
    printf("Mesh loaded : %s (%d vertices, %d triangles)\n", path, new_mesh->nb_vertices, new_mesh->nb_triangles);
    new_mesh->reflectivity = reflectivity;
    add_mesh(w, new_mesh);
    fclose(file);
}


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
    int norm_vert = 0;
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
            if(line[1] == 'n')
                norm_vert++;
        }
        else if (line[0] == 'f')
        {
            int space = 0;
            for (int i = 1; line[i] != 0 && line[i] != '\r'; i++)
            {
                if (line[i] != ' ' && line[i-1] == ' ')
                    space++;
            }
            tri = tri + (space-3) +1;
        }
    }
    if(vert == 0 || tri == 0){
        printf("The %s file is not a valid obj file\n", path);
        return;
    }
    
    mesh* new_mesh = build_mesh(vert, tri, text_vert, norm_vert);
    fseek(file, 0, SEEK_SET);

    float v[3];
    float vn[3];
    float vt[2];
    while(fgets(line, sizeof(line), file) != NULL)
    {
        if (line[0] == 'v')
        {
            if (line[1] == ' '){
                sscanf(line, "v %f %f %f", &v[0], &v[1], &v[2]);
                scale(v, scale, v);
                add(v, pos, v);
                add_v(new_mesh, v);
            }
            if(line[1] == 't'){
                sscanf(line, "vt %f %f", &vt[0], &vt[1]);
                add_vt(new_mesh, vt);
            }
            if(line[1] == 'n'){
                sscanf(line, "vn %f %f %f", &vn[0], &vn[1], &vn[2]);
                add_vn(new_mesh, vn);
            }
        }

        if (line[0] == 'f' && line[1] == ' ')
        {
            int nb_v = 0;
            // v vt vn
            int* vs[3] = {NULL,NULL,NULL} ;
            int cur_v = 0;
            int cur_nb = 0;
            int i = 1;
            int last_space = 1;
            while (line[i] != '\0' && line[i] != '\r')
            {
                switch (line[i])
                {
                case '/':
                    vs[cur_v][nb_v-1] = cur_nb;
                    cur_v++;
                    cur_nb = 0;
                    break;
                case ' ':
                    last_space = 1;
                    break;
                default:
                    if(last_space){
                        nb_v++;
                        for(int i = 0; i < 3; i++)
                            vs[i] = realloc(vs[i], sizeof(int)*nb_v);
                        cur_nb = 0;
                        cur_v = 0;
                        last_space = 0;
                    }
                    int val = atoi(&line[i]);
                    cur_nb = val;
                    val/=10;
                    while(val != 0){
                        val/=10;
                        i++;
                    }
                    break;
                }
                i++;
            }
            int v[3];
            int vt[3];
            int vn[3];
            for (int j = 0; j < nb_v-2; j++)
            {
                v[0] = vs[0][0] - 1;
                v[1] = vs[0][j+1] -1;
                v[2] = vs[0][j+2] -1;

                vt[0] = vs[1][0] - 1;
                vt[1] = vs[1][j+1] - 1;
                vt[2] = vs[1][j+2] - 1;

                vn[0] = vs[2][0] - 1;
                vn[1] = vs[2][j+1] - 1;
                vn[2] = vs[2][j+2] - 1;
                add_tri(new_mesh, v, vt, vn);
            }
            for (int i = 0; i < 3; i++)
                free(vs[i]);
            
        }
    }

    if(texture_path != NULL){
        load_texture(new_mesh, texture_path);
    }else{
        new_mesh->texture = NULL;
    }
    printf("Bbox of the object created: from %f %f %f to %f %f %f\n", new_mesh->box->min[0], new_mesh->box->min[1], new_mesh->box->min[2], new_mesh->box->max[0], new_mesh->box->max[1], new_mesh->box->max[2]);
    printf("Mesh loaded : %s (%d vertices, %d triangles)\n", path, new_mesh->nb_vertices, new_mesh->nb_triangles);
    new_mesh->reflectivity = reflectivity;
    add_mesh(w, new_mesh);
    fclose(file);
}


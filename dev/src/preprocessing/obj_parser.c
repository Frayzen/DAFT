#include "../../include/preprocessing/obj_parser.h"

void rotate(float* p, float rotX, float rotY, float rotZ){
    float tmp[3];
    tmp[0] = p[0];
    tmp[1] = p[1];
    tmp[2] = p[2];
    if(rotX != 0){
        p[1] = tmp[1] * cos(rotX) - tmp[2] * sin(rotX);
        p[2] = tmp[1] * sin(rotX) + tmp[2] * cos(rotX);
    }
    if(rotY != 0){
        p[0] = tmp[0] * cos(rotY) + tmp[2] * sin(rotY);
        p[2] = -tmp[0] * sin(rotY) + tmp[2] * cos(rotY);
    }
    if(rotZ != 0){
        p[0] = tmp[0] * cos(rotZ) - tmp[1] * sin(rotZ);
        p[1] = tmp[0] * sin(rotZ) + tmp[1] * cos(rotZ);
    }
}

int load_object(char *path, world *w, float scale, float pos[3], float rot[3], char *rel_path)
{
    FILE *file;
    file = fopen(path, "r");
    if (file == NULL)
    {
        printf("Cant open the file named '%s'\n", path);
        return 0;
    }

    int vert = 0;
    int tri = 0;
    int text_vert = 0;
    int norm_vert = 0;
    // size_t norm = 0;
    // size_t texture = 0;

    char line[200];
    material *mats = NULL;
    int nb_mat = 0;

    while (fgets(line, sizeof(line), file) != NULL)
    {
        if (line[0] == 'v')
        {
            if (line[1] == ' ')
                vert++;
            if (line[1] == 't')
                text_vert++;
            if (line[1] == 'n')
                norm_vert++;
        }
        else if (line[0] == 'f')
        {
            int space = 0;
            for (int i = 1; line[i] != 0 && line[i] != '\r'; i++)
            {
                if (line[i] != ' ' && line[i - 1] == ' ')
                    space++;
            }
            tri = tri + (space - 3) + 1;
        }
        else if (strncmp(line, "mtllib", 6) == 0)
        {
            char tmp[50];
            sscanf(line, "mtllib %s", tmp);
            printf("Loading material file : %s\n", tmp);
            char cpy_path[50];
            strcpy(cpy_path, rel_path);
            strcat(cpy_path, tmp);
            printf("Path : %s \n", cpy_path);
            mtl_parser(cpy_path, rel_path, &mats, &nb_mat);
        }
    }
    if (vert == 0 || tri == 0)
    {
        printf("The %s file is not a valid obj file\n", path);
        return 0;
    }

    mesh *new_mesh = build_mesh(vert, tri, text_vert, norm_vert);
    fseek(file, 0, SEEK_SET);

    float v[3];
    float vn[3];
    float vt[2];
    material *curr = NULL;

    float rotX = rot[0] * M_PI / 180;
    float rotY = rot[1] * M_PI / 180;
    float rotZ = rot[2] * M_PI / 180;

    while (fgets(line, sizeof(line), file) != NULL)
    {
        if (line[0] == 'v')
        {
            if (line[1] == ' ')
            {
                sscanf(line, "v %f %f %f", &v[0], &v[1], &v[2]);
                rotate(v, rotX, rotY, rotZ);
                scale(v, scale, v);
                add(v, pos, v);
                add_v(new_mesh, v);
            }
            if (line[1] == 't')
            {
                sscanf(line, "vt %f %f", &vt[0], &vt[1]);
                add_vt(new_mesh, vt);
            }
            if (line[1] == 'n')
            {
                sscanf(line, "vn %f %f %f", &vn[0], &vn[1], &vn[2]);
                add_vn(new_mesh, vn);
            }
        }

        if (line[0] == 'f' && line[1] == ' ')
        {
            int nb_v = 1;
            // v vt vn
            int *vs[3] = {malloc(sizeof(int)), malloc(sizeof(int)), malloc(sizeof(int))};
            int cur_v = 0;
            int cur_nb = 0;
            int i = 2;
            int last_space = 0;
            while (line[i] != '\0' && line[i] != '\r')
            {
                switch (line[i])
                {
                case '\n':
                    break;
                case '/':
                    last_space = 0;
                    cur_v++;
                    break;
                case ' ':
                    if (!last_space)
                    {
                        if(line[i+1]){
                            char tmp_chr = line[i+1];
                            if(tmp_chr == ' ' || tmp_chr == '\n' || tmp_chr == '\r')
                                break;
                        }
                        nb_v++;
                        for (int i = 0; i < 3; i++)
                            vs[i] = realloc(vs[i], sizeof(int) * nb_v);
                        cur_nb = 0;
                        cur_v = 0;
                    }
                    last_space = 1;
                    break;
                default:
                    last_space = 0;
                    int val = atoi(&line[i]);
                    cur_nb = val;
                    val /= 10;
                    while (val != 0)
                    {
                        val /= 10;
                        i++;
                    }
                    vs[cur_v][nb_v - 1] = cur_nb;
                    break;
                }
                i++;
            }

            int v[3];
            int vt[3];
            int vn[3];
            for (int j = 0; j < nb_v - 2; j++)
            {
                v[0] = vs[0][0] - 1;
                if (v[0] < 0)
                    v[0] += vert;
                v[1] = vs[0][j + 1] - 1;
                if (v[1] < 0)
                    v[1] += vert;
                v[2] = vs[0][j + 2] - 1;
                if (v[2] < 0)
                    v[2] += vert;

                vt[0] = vs[1][0] - 1;
                if (vt[0] < 0)
                    vt[0] += text_vert;
                vt[1] = vs[1][j + 1] - 1;
                if (vt[1] < 0)
                    vt[1] += text_vert;
                vt[2] = vs[1][j + 2] - 1;
                if (vt[2] < 0)
                    vt[2] += text_vert;

                vn[0] = vs[2][0] - 1;
                if (vn[0] < 0)
                    vn[0] += norm_vert;
                vn[1] = vs[2][j + 1] - 1;
                if (vn[1] < 0)
                    vn[1] += norm_vert;
                vn[2] = vs[2][j + 2] - 1;
                if (vn[2] < 0)
                    vn[2] += norm_vert;
                add_tri(new_mesh, v, vt, vn, curr);
            }
            for (int i = 0; i < 3; i++)
                free(vs[i]);
        }
    }
    /*
    if(texture_path != NULL){
        load_texture(mat, texture_path);
    }else{
        if(mat == NULL){
            printf("No material given, creating a default one\n");
            mat = def_mat(1,1,1,4,0);
        }
    }
    if(texture_path != NULL){
        load_texture(mats, texture_path);
    }else{

        if(mats == NULL){
            printf("No material given, creating a default one\n");
            mats = def_mat(1,1,1,4,0);
        }
        mats->texture = NULL;
        //load_texture(mats, "./assets/textures/leather_white_diff_4k.jpg");
    }
    */
    printf("Bbox of the object created: from %f %f %f to %f %f %f\n", new_mesh->box->min[0], new_mesh->box->min[1], new_mesh->box->min[2], new_mesh->box->max[0], new_mesh->box->max[1], new_mesh->box->max[2]);
    printf("Mesh loaded : %s (%d vertices, %d triangles)\n", path, new_mesh->nb_vertices, new_mesh->nb_triangles);
    new_mesh->mats = mats;
    new_mesh->nb_mat = nb_mat;
    // print all the mats
    for (int i = 0; i < new_mesh->nb_mat; i++)
    {
        printf("Material %d\n", i);
        printf("ka is %f %f %f\n", new_mesh->mats[i].ambient[0], new_mesh->mats[i].ambient[1], new_mesh->mats[i].ambient[2]);
        printf("kd is %f %f %f\n", new_mesh->mats[i].diffuse[0], new_mesh->mats[i].diffuse[1], new_mesh->mats[i].diffuse[2]);
        printf("ks is %f %f %f\n", new_mesh->mats[i].specular[0], new_mesh->mats[i].specular[1], new_mesh->mats[i].specular[2]);
    }
    add_mesh(w, new_mesh);
    fclose(file);
    return 1;
}

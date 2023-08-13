#include "../../include/preprocessing/obj_parser.h"

void rotate(float3* r, float rotX, float rotY, float rotZ){
    float3 p = *r;
    float3 tmp;
    copy(p, tmp);
    if(rotX != 0){
        p.y = tmp.y * cos(rotX) - tmp.z * sin(rotX);
        p.z = tmp.y * sin(rotX) + tmp.z * cos(rotX);
    }
    if(rotY != 0){
        p.x = tmp.x * cos(rotY) + tmp.z * sin(rotY);
        p.z = -tmp.x * sin(rotY) + tmp.z * cos(rotY);
    }
    if(rotZ != 0){
        p.x = tmp.x * cos(rotZ) - tmp.y * sin(rotZ);
        p.y = tmp.x * sin(rotZ) + tmp.y * cos(rotZ);
    }
}

int load_object(char *path, world *w, float scale, float3 pos, float3 rot, char *rel_path)
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

    mesh *new_mesh = init_mesh(vert, tri, text_vert, norm_vert);
    fseek(file, 0, SEEK_SET);

    float3 v;
    float3 vn;
    float2 vt;
    int mat_id = 0;

    float rotX = rot.x * M_PI / 180;
    float rotY = rot.y * M_PI / 180;
    float rotZ = rot.z * M_PI / 180;

    while (fgets(line, sizeof(line), file) != NULL)
    {
        if (line[0] == 'v')
        {
            if (line[1] == ' ')
            {
                sscanf(line, "v %f %f %f", &v.x, &v.y, &v.z);
                rotate(&v, rotX, rotY, rotZ);
                scale(v, scale, v);
                add(v, pos, v);
                add_v(new_mesh, v);
            }
            if (line[1] == 't')
            {
                sscanf(line, "vt %f %f", &vt.x, &vt.y);
                add_vt(new_mesh, vt);
            }
            if (line[1] == 'n')
            {
                sscanf(line, "vn %f %f %f", &vn.x, &vn.y, &vn.z);
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

            int3 v;
            int3 vt;
            int3 vn;
            for (int j = 0; j < nb_v - 2; j++)
            {
                v.p1 = vs[0][0] - 1;
                if (v.p1 < 0)
                    v.p1 += vert;
                v.p2 = vs[0][j + 1] - 1;
                if (v.p2 < 0)
                    v.p2 += vert;
                v.p3 = vs[0][j + 2] - 1;
                if (v.p3 < 0)
                    v.p3 += vert;

                vt.p1 = vs[1][0] - 1;
                if (vt.p1 < 0)
                    vt.p1 += text_vert;
                vt.p2 = vs[1][j + 1] - 1;
                if (vt.p2 < 0)
                    vt.p2 += text_vert;
                vt.p3 = vs[1][j + 2] - 1;
                if (vt.p3 < 0)
                    vt.p3 += text_vert;

                vn.p1 = vs[2][0] - 1;
                if (vn.p1 < 0)
                    vn.p1 += norm_vert;
                vn.p2 = vs[2][j + 1] - 1;
                if (vn.p2 < 0)
                    vn.p2 += norm_vert;
                vn.p3 = vs[2][j + 2] - 1;
                if (vn.p3 < 0)
                    vn.p3 += norm_vert;
                add_tri(new_mesh, v, vt, vn, mat_id);
            }
            for (int i = 0; i < 3; i++)
                free(vs[i]);
        }
        if (strncmp(line, "mtllib", 6) == 0){
            mat_id++;
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
    printf("Mesh loaded : %s (%d vertices, %d triangles)\n", path, new_mesh->vs_size, new_mesh->tri_size);
    new_mesh->mats = mats;
    new_mesh->mat_size = nb_mat;
    // print all the mats
    for (int i = 0; i < new_mesh->mat_size; i++)
    {
        printf("Material %d\n", i);
        printf("ka is %f %f %f\n", new_mesh->mats[i].ambient.x, new_mesh->mats[i].ambient.y, new_mesh->mats[i].ambient.z);
        printf("kd is %f %f %f\n", new_mesh->mats[i].diffuse.x, new_mesh->mats[i].diffuse.y, new_mesh->mats[i].diffuse.z);
        printf("ks is %f %f %f\n", new_mesh->mats[i].specular.x, new_mesh->mats[i].specular.y, new_mesh->mats[i].specular.z);
    }
    build_mesh(new_mesh);
    add_mesh(w, new_mesh);
    fclose(file);
    return 1;
}

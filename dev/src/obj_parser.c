#include "../include/obj_parser.h"

void load_object(world* w, char* file, float scale){
    FILE *fp;
    fp = fopen(file, "r");
    if(fp == NULL){
        printf("File '%s' not found\n", file);
        return;
    }
    char line[128];
    size_t vertex_count = 0;
    size_t face_count = 0;
    while(fgets(line, sizeof(line), fp) != NULL){
        if(line[0] == 'v'){
            vertex_count++;
        }
        if(line[0] == 'f'){
            face_count++;
        }
    }
    mesh* m = init_mesh(vertex_count, face_count, w->size_m);
    rewind(fp);
    point p;
    while(fgets(line, sizeof(line), fp) != NULL){
        if(line[0] == 'v' && line[1] == ' '){
            sscanf(line, "v %f %f %f", &p.x, &p.y, &p.z);
            p.x*=scale;
            p.y*=scale;
            p.z*=scale;
            add_vertex(m, m->v_size, p.x, p.y, p.z);
        }
        if(line[0] == 'f'){
            int v1, v2, v3;
            int vt1, vt2, vt3;
            int vn1, vn2, vn3;
            sscanf(line, "f %d/%d/%d %d/%d/%d %d/%d/%d", &v1, &vt1, &vn1, &v2, &vt2, &vn2, &v3, &vt3, &vn3);
            add_tri(m, m->t_size, v1, v2, v3);
        }
    }
    printf("Loaded %lu verticles and %lu faces \n", m->v_size, m->t_size);
    fclose(fp);
}


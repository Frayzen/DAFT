#include "../include/obj_parser.h"

void load_object(world* w, char* file, float scale, point pos){
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
    size_t faceloaded = 0;
    while(fgets(line, sizeof(line), fp) != NULL){
        if(line[0] == 'v' && line[1] == ' '){
            sscanf(line, "v %le %le %le", &p.x, &p.y, &p.z);
            p.x*=scale;
            p.y*=scale;
            p.z*=scale;
            addp(&p, &pos);
            add_vertex(m, p.x, p.y, p.z);
        }
        if(line[0] == 'f'){
            int v1, v2, v3;
            int vt1, vt2, vt3;
            int vn1, vn2, vn3;
            if(sscanf(line, "f %d/%d/%d %d/%d/%d %d/%d/%d", &v1, &vt1, &vn1, &v2, &vt2, &vn2, &v3, &vt3, &vn3) != 6)
                sscanf(line, "f %d %d %d", &v1,&v2,&v3);
            add_tri(m, v1-1, v2-1, v3-1);
            faceloaded++;
        }
    }
    add_mesh(w, m);
    printf("Loaded %lu verticles and %lu faces \n", m->v_size, faceloaded);
    fclose(fp);
}


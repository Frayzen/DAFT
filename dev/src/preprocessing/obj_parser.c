#include "../../include/preprocessing/obj_parser.h"

void load_object(world* w, char* file, float scale, float pos[3]){
    FILE *fp;
    fp = fopen(file, "r");
    if(fp == NULL){
        printf("File '%s' not found\n", file);
        return;
    }
    char line[128];
    int vertex_count = 0;
    int face_count = 0;
    while(fgets(line, sizeof(line), fp) != NULL){
        if(line[0] == 'v'){
            vertex_count++;
        }
        if(line[0] == 'f'){
            face_count++;
        }
    }
    mesh* m = build_mesh(vertex_count, face_count, w->size_meshes);
    rewind(fp);
    float p[3];
    int faceloaded = 0;
    while(fgets(line, sizeof(line), fp) != NULL){
        if(line[0] == 'v' && line[1] == ' '){
            sscanf(line, "v %f %f %f", &p[0], &p[1], &p[2]);
            scale(p, scale, p);
            add(p, pos, p);
            add_vertex(m, p);
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
    printf("Loaded %i verticles and %i faces \n", m->nb_vertices, faceloaded);
    fclose(fp);
}


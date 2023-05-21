#include "../../include/architecture/material.h"

//shininess more than 1
//reflection less than 1
material* mat_init(float r, float g, float b, float ambient[3], float diffuse[3], float specular[3], float shininess, float reflection){
    material* mat = malloc(sizeof(material));
    mat->color[0] = r;
    mat->color[1] = g;
    mat->color[2] = b;
    copy(ambient, mat->ambient);
    copy(diffuse, mat->diffuse);
    copy(specular, mat->specular);
    mat->shininess = shininess;
    mat->reflection = reflection;
    mat->texture = NULL;
    return mat;
}

void mtl_parser(const char* filename, material** materials, int* numMaterials)
{
    FILE* file = fopen(filename, "r");
    if (file == NULL) {
        printf("Failed to open MTL file: %s\n", filename);
        return NULL;
    }
    int maxMaterials = 10;
    *numMaterials = 0;
    *materials = (material*) malloc(maxMaterials * sizeof(material));
    char line[256];

    while (fgets(line, 256, file) != NULL) {
        if (strncmp(line, "newmtl", 6) == 0) {           //We are on a new material
            if (*numMaterials >= maxMaterials) {
                maxMaterials *= 2;
                *materials = (material*)realloc(*materials, maxMaterials * sizeof(material));
            }
            //sscanf(line, "newmtl %[^\n]", (*materials)[*numMaterials].name);
            (*numMaterials)++;
        }
        else if (strncmp(line, "Ka", 2) == 0) {          //Ambiant color of the material
            sscanf(line, "Ka %f %f %f", &(*materials)[*numMaterials - 1].ambient[0],
                &(*materials)[*numMaterials - 1].ambient[1], &(*materials)[*numMaterials - 1].ambient[2]);
        }
        else if (strncmp(line, "Kd", 2) == 0) {          //Difuse color
            sscanf(line, "Kd %f %f %f", &(*materials)[*numMaterials - 1].diffuse[0],
                &(*materials)[*numMaterials - 1].diffuse[1], &(*materials)[*numMaterials - 1].diffuse[2]);
        }
        else if (strncmp(line, "Ks", 2) == 0) {          //Specular color
            sscanf(line, "Ks %f %f %f", &(*materials)[*numMaterials - 1].specular[0],
                &(*materials)[*numMaterials - 1].specular[1], &(*materials)[*numMaterials - 1].specular[2]);
        }
        else if (strncmp(line, "Ns", 2) == 0) {          //Shininess
            sscanf(line, "Ns %f", &(*materials)[*numMaterials - 1].shininess);
        }
        else{
            continue;
        }
    }

    fclose(file);
}
material* create_mat_from_color(float r, float g, float b){
    return mat_init(r, g, b, (float[]){0.1,0.1,0.1}, (float[]){.8,.8,.8}, (float[]){1,1,1}, .2, 0);
}

material* def_mat(float r, float g, float b, float shininess, float reflection){
    return mat_init(r, g, b, (float[]){0.4,0.4,0.4}, (float[]){1,1,1}, (float[]){.8,.8,.8}, shininess, reflection);
}
material* default_mat(){
    return def_mat(1,1,1,50,0);
}


void load_texture(material* m, char* path){
    SDL_Surface* surface = IMG_Load(path);
    if(surface == NULL){
        printf("Could not load the texture '%s'\n", path);
        return;
    }
    m->texture = SDL_ConvertSurfaceFormat(surface, SDL_PIXELFORMAT_RGBA8888, 0);
    SDL_FreeSurface(surface);
    printf("Texture '%s' loaded successfully !\n", path);
}
void free_mat(material* m){
    if(m->texture != NULL)
        SDL_FreeSurface(m->texture);
    free(m);
}

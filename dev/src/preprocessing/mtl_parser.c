#include "../../include/preprocessing/mtl_parser.h"

void mtl_parser(const char* filename, material** materials, int* numMaterials)
{
    FILE* file = fopen(filename, "r");
    if (file == NULL) {
        printf("Failed to open MTL file: %s\n", filename);
        return;
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
            sscanf(line, "newmtl %[^\n]", (*materials)[*numMaterials].name);
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

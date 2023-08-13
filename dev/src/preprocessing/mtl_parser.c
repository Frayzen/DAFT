#include "../../include/preprocessing/mtl_parser.h"

void setup_mat(material* mat){
    float3 default_ks = {0.2, 0.2, 0.2};
    float3 default_ka = {0.5, 0.5, 0.5};
    float3 default_kd = {0.5, 0.5, 0.5};
    copy(default_kd, mat->diffuse);
    copy(default_ka, mat->ambient);
    copy(default_ks, mat->specular);
    mat->ambientText = NULL;
    mat->diffuseText = NULL;
    mat->specularText = NULL;
    mat->shininess = 10;
    mat->reflection = 0;
}

void mtl_parser(const char *filename, const char* path, material **materials, int *numMaterials)
{
    FILE *file = fopen(filename, "r");
    if (file == NULL)
    {
        printf("Failed to open MTL file: %s\n", filename);
        return;
    }
    int maxMaterials = 10;
    *numMaterials = 0;
    *materials = (material *)malloc(maxMaterials * sizeof(material));

    char line[256];
    while (fgets(line, 256, file) != NULL)
    {
        if (strncmp(line, "newmtl", 6) == 0)
        { // We are on a new material
            if (*numMaterials >= maxMaterials)
            {
                maxMaterials *= 2;
                *materials = (material *)realloc(*materials, maxMaterials * sizeof(material));
            }
            sscanf(line, "newmtl %[^\n]", (*materials)[*numMaterials].name);
            (*numMaterials)++;
            setup_mat(&(*materials)[*numMaterials - 1]);
        }
        else if (strncmp(line, "Ka", 2) == 0)
        { // Ambiant color of the material
            sscanf(line, "Ka %f %f %f", &(*materials)[*numMaterials - 1].ambient.x,
                   &(*materials)[*numMaterials - 1].ambient.y, &(*materials)[*numMaterials - 1].ambient.z);
        }
        else if (strncmp(line, "Kd", 2) == 0)
        { // Difuse color
            sscanf(line, "Kd %f %f %f", &(*materials)[*numMaterials - 1].diffuse.x,
                   &(*materials)[*numMaterials - 1].diffuse.y, &(*materials)[*numMaterials - 1].diffuse.z);
        }
        else if (strncmp(line, "Ks", 2) == 0)
        { // Specular color
            sscanf(line, "Ks %f %f %f", &(*materials)[*numMaterials - 1].specular.x,
                   &(*materials)[*numMaterials - 1].specular.y, &(*materials)[*numMaterials - 1].specular.z);
        }
        else if (strncmp(line, "Ns", 2) == 0)
        { // Shininess
            sscanf(line, "Ns %f", &(*materials)[*numMaterials - 1].shininess);
        }
        // else if (strncmp(line, "d", 1) == 0)
        // { // Reflection
        //     printf("line: %s\n", line);
        //     sscanf(line, "d %f", &(*materials)[*numMaterials - 1].reflection);
        // }
        else if (strncmp(line, "map_Kd", 6) == 0)
        { // Texture
            char texture_name[256];
            sscanf(line, "map_Kd %s", texture_name);
            char path_texture[256];
            strcpy(path_texture, path);
            strcat(path_texture, texture_name);
            load_texture(&(*materials)[*numMaterials - 1].diffuseText, path_texture);
            printf("Diffuse texture : %s\n", path_texture);
        }
        else if(strncmp(line, "map_Ks", 6) == 0)
        { // Specular texture
            char texture_name[256];
            sscanf(line, "map_Ks %s", texture_name);
            char path_texture[256];
            strcpy(path_texture, path);
            strcat(path_texture, texture_name);
            load_texture(&(*materials)[*numMaterials - 1].specularText, path_texture);
        }
        else if(strncmp(line, "map_Ka", 6) == 0)
        { // Ambient texture
            char texture_name[256];
            sscanf(line, "map_Ka %s", texture_name);
            char path_texture[256];
            strcpy(path_texture, path);
            strcat(path_texture, texture_name);
            load_texture(&(*materials)[*numMaterials - 1].ambientText, path_texture);
        }
        else
        {
            continue;
        }
    }
    fclose(file);
}

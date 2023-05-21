#include "../../include/preprocessing/mtl_parser.h"

material** load_mtl(char* path)
{
    size_t nb_mat = 0;
    FILE* file;

    file = fopen(path, "r");
    if (file == NULL)
    {
        printf("unable to open mtl file\n");
        return NULL;
    }

    char line[256];
    while (fgets(line, sizeof(line), file) != NULL)
    {
        if (line[0] == 'n')
            nb_mat++;
    }
    printf("nb %ld\n", nb_mat);
    fseek(file, 0, SEEK_SET);

    material** mats = malloc(nb_mat*sizeof(material*));
    material* curr = NULL;
    size_t i = 0;
    float r = 0; float g = 0; float b = 0;
    float ambient[3]; float diffuse[3]; float specular[3];
    float shininess = 0; float reflection = 0;

    while (fgets(line, sizeof(line), file) != NULL)
    {
        if (strncmp(line, "newmtl", 6) == 0)
        {
            printf("i %ld\n", i);
            curr = mat_init(r, g, b, ambient, diffuse, specular, shininess, 
                    reflection);
            mats[i] = curr;
            i++;
        }
        if (strncmp(line, "Ka", 2) == 0)
            sscanf(line, "Ka %f %f %f", &curr->ambient[0], &curr->ambient[1], 
                    &curr->ambient[2]);
        if (strncmp(line, "Kd", 2) == 0)
            sscanf(line, "Kd %f %f %f", &curr->diffuse[0], &curr->diffuse[1],
                    &curr->diffuse[2]);
        if (strncmp(line, "Ks", 2) == 0)
            sscanf(line, "Ks %f %f %f", &curr->specular[0], &curr->specular[1],
                    &curr->specular[2]);
        if (strncmp(line, "Ns", 2) == 0)
            sscanf(line, "Ns %f", &curr->shininess);
        if (strncmp(line, "d", 1) == 0)
            sscanf(line, "d %f", &curr->reflection);
        if (strncmp(line, "map_kd", 6) == 0)
        {
            char* txt_path = "";
            sscanf(line, "map_kd %s", txt_path);
            load_texture(curr, txt_path);
        }
    }
    /*
    printf("ambient %f %f %f\n", mats[0]->ambient[0], mats[0]->ambient[1], mats[0]->ambient[2]);
    printf("diffuse %f %f %f\n", mats[0]->diffuse[0], mats[0]->diffuse[1], mats[0]->diffuse[2]);
    printf("specular %f %f %f\n",mats[0]->specular[0], mats[0]->specular[1], mats[0]->specular[2]);

    printf("ambient %f %f %f\n", mats[1]->ambient[1], mats[1]->ambient[1], mats[1]->ambient[2]);
    printf("diffuse %f %f %f\n", mats[1]->diffuse[0], mats[1]->diffuse[1], mats[1]->diffuse[2]);
    printf("specular %f %f %f\n",mats[1]->specular[0], mats[1]->specular[1], mats[1]->specular[2]);
    */

    return mats;
}

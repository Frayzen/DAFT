#include "../../include/preprocessing/scene_parser.h"

int startsWith(const char *pre, const char *str)
{
    size_t lenpre = strlen(pre),
           lenstr = strlen(str);
    return lenstr < lenpre ? 0 : strncmp(pre, str, lenpre) == 0;
}

material *load_mat(char *path)
{
    return default_mat();
}

world *load_scene(char *path)
{
    int pthlen = strlen(path);
    char path_copy[pthlen + 1];
    strcpy(path_copy, path);
    path_copy[pthlen] = 0;
    
    #ifdef _WIN32
    char _dir_name[200];
    _splitpath(path_copy, NULL, _dir_name, NULL, NULL);
    #else
    char *_dir_name = dirname(path_copy);
    #endif
    char dir_name[strlen(_dir_name) + 1];
    strcpy(dir_name, _dir_name);
    #ifndef _WIN32
    strcat(dir_name, "/");
    #endif
    printf("Dir: %s\n", dir_name);

    FILE *file = fopen(path, "r");
    if (file == NULL)
    {
        printf("Can't open the file named '%s'\n", path);
        return NULL;
    }
    printf("file first char: %d\n", *file);

    world *wd = init_world();
    char skybox_path[200] = "";
    float3 cam_pos;
    float cam_pitch = 0;
    float cam_yaw = 0;
    float cam_fov = 90;
    printf("World initialized\n");
    printf("=== Loading scene ===\n");
    float p[20];
    char mesh_path[200];
    char material_path[200];
    char line[200];
    int i = 0;
    while (fgets(line, sizeof(line), file) != NULL)
    {   
        i++;
        mesh_path[0] = '\0';
        material_path[0] = '\0';
        memset(p, 0, sizeof(p));
        // camera x y z pitch yaw fov(default 90)
        if (startsWith("camera ", line))
        {
            sscanf(line, "camera %f %f %f %f %f %f", &cam_pos.x, &cam_pos.y, &cam_pos.z, &cam_pitch, &cam_yaw, &cam_fov);
            printf("Camera initialized\n");
            continue;
        }

        // skybox path
        if (startsWith("skybox ", line))
        {
            sscanf(line, "skybox %s", skybox_path);
            printf("Skybox loaded\n");
            continue;
        }
        //rotations in degree
        // mesh mesh_path x y z scale rot_x rot_y rot_z
        if (startsWith("mesh ", line))
        {
            sscanf(line, "mesh %s %f %f %f %f %f %f %f", mesh_path, &p[0], &p[1], &p[2], &p[3], &p[4], &p[5], &p[6]);
            char dir_name_cpy[200];
            strcpy(dir_name_cpy, dir_name);
            if(load_object(strcat(dir_name_cpy, mesh_path), wd, p[3], (float3){p[0], p[1], p[2]}, (float3){p[4], p[5], p[6]}, dir_name))
                printf("Mesh %s loaded\n", mesh_path);
            continue;
        }
        // light x y z r g b
        if (startsWith("light ", line))
        {
            sscanf(line, "light %f %f %f %f %f %f", &p[0], &p[1], &p[2], &p[3], &p[4], &p[5]);
            light *lt = init_light((float3){p[0], p[1], p[2]}, (float3){p[3], p[4], p[5]});
            add_light(wd, lt);
            printf("Light loaded\n");
            continue;
        }

        // sphere x y z r material_path
        if (startsWith("sphere ", line))
        {
            sscanf(line, "sphere %f %f %f %f %s", &p[0], &p[1], &p[2], &p[3], material_path);
            char dir_name_cpy[200];
            strcpy(dir_name_cpy, dir_name);
            sphere *sph = sphere_init((float3){p[0], p[1], p[2]}, p[3], load_mat(strcat(dir_name_cpy, material_path)));
            add_sphere(wd, sph);
            printf("Sphere initialized\n");
            continue;
        }
    }

    light *lt2 = init_light((float3){-10, 0, 0}, (float3){1, 1, 1});
    add_light(wd, lt2);

    if (strlen(skybox_path) != 0)
    {
        char dir_name_cpy[200];
        strcpy(dir_name_cpy, dir_name);
        strcat(dir_name_cpy, skybox_path);
        load_skybox(wd, dir_name_cpy);
    }
    if (cam_fov == 0)
        cam_fov = 90;
    camera *cam = init_camera(cam_pos, cam_pitch, cam_yaw, cam_fov, cam_fov);
    add_camera(wd, cam);
    printf("=== Scene loaded ===\n");
    //check if file is closed
    printf("file first char: %d\n", *file);
    return wd;
}
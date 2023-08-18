#define DEBUG 0
#if DEBUG == 1
#define SCREEN_WIDTH 3
#define SCREEN_HEIGHT 3
#else
#define SCREEN_WIDTH 300
#define SCREEN_HEIGHT 200
#endif
#define SCREEN_ASPECT_RATIO ((float)SCREEN_WIDTH/(float)SCREEN_HEIGHT)
#define CAM_MOV_SPEED 0.1
#define MOVING_SPEED 0.01
#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif
#define CAM_FOV 90 * M_PI / 180
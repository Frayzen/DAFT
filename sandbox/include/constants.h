#define DEBUG 0

#if DEBUG == 1
#define SCREEN_WIDTH 10
#define SCREEN_HEIGHT 10
#else
#define SCREEN_WIDTH 640
#define SCREEN_HEIGHT 480
#endif
#define SCREEN_ASPECT_RATIO ((float)SCREEN_WIDTH/(float)SCREEN_HEIGHT)
#define CAM_FOV 90
#define CAM_MOV_SPEED 0.1
#define MOVING_SPEED 0.01
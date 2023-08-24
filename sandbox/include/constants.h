#define DEBUG 0

#if DEBUG == 1
#define SCREEN_WIDTH 3
#define SCREEN_HEIGHT 3
#else
#define SCREEN_WIDTH 500
#define SCREEN_HEIGHT 500
#endif
#define SCREEN_ASPECT_RATIO ((float)SCREEN_WIDTH/(float)SCREEN_HEIGHT)

#define CAM_MOV_SPEED 0.1
#define MOVING_SPEED 0.01

#define FULLSCREEN 0

#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif
#define CAM_FOV 90 * M_PI / 180

#define UP_KEY SDLK_SPACE
#define DOWN_KEY SDLK_LSHIFT

#define KEYBOARD_AZERTY 1

#if KEYBOARD_AZERTY == 1
#define FORW_KEY SDLK_z
#define BACK_KEY SDLK_s
#define LEFT_KEY SDLK_q
#define RIGHT_KEY SDLK_d
#else
#define FORW_KEY SDLK_w
#define BACK_KEY SDLK_s
#define LEFT_KEY SDLK_a
#define RIGHT_KEY SDLK_d
#endif
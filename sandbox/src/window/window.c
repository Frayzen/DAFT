#include "../../include/window/window.h"

DaftApp* initApp(){
    DaftApp* app = calloc(sizeof(DaftApp), 1);
    app->world = createWorld();
    app->camera = NULL;
    app->openCL = initOpenCL();
    omp_set_num_threads(omp_get_num_procs());
    SDL_Init(SDL_INIT_VIDEO);
    IMG_Init(IMG_INIT_PNG);
    SDL_SetHint( SDL_HINT_RENDER_SCALE_QUALITY, "1" );
    app->window = SDL_CreateWindow("SDL2 Displaying Image",
            SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
            SCREEN_WIDTH, SCREEN_HEIGHT, 0);
    app->renderer = SDL_CreateRenderer(app->window, -1, SDL_RENDERER_ACCELERATED);
    SDL_SetRelativeMouseMode(SDL_TRUE);
    SDL_RendererInfo info;
    SDL_GetRendererInfo(app->renderer, &info );
    //pixels
    app->texture = SDL_CreateTexture(app->renderer, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_STREAMING, SCREEN_WIDTH, SCREEN_HEIGHT);
    Uint32* pixels;
    int pitch;
    SDL_LockTexture(app->texture, NULL, (void**)&pixels, &pitch);
    return app;
}

void freeApp(DaftApp* app){
    freeWorld(app->world);
    if(app->camera != NULL)
        free(app->camera);
    SDL_DestroyRenderer(app->renderer); 
    SDL_DestroyWindow(app->window);
    SDL_DestroyTexture(app->texture);
    SDL_Quit();
}

void launchScreen(DaftApp* app){
    int quit = 0;
    time_t last = time(NULL);
    int fps = 0;
    SDL_Texture* texture = SDL_CreateTextureFromSurface(app->renderer, app->world->skybox);
    while (!quit)
    {
        //quit = 1;
        
        renderScreen(app, texture);
        if(app->world->skybox != NULL){
            defineSkyPoints(app, texture);
            SDL_SetTextureBlendMode(app->texture, SDL_BLENDMODE_BLEND);
        }
        SDL_RenderCopy(app->renderer, app->texture, NULL, NULL); 
        SDL_RenderPresent(app->renderer);
        fps++;
        if(last != time(NULL)){
            printf("%i fps\n", fps);
            fps = 0;
            last = time(NULL);
        }
        handle_events(&quit, app);
    }
}


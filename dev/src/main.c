#include "../include/image_renderer.h"
#include <stdio.h>
int main(){
    app_params params;
    params.width = 800;
    params.height = 500;
    params.FPS_UPPER_LIMIT=30;
    setup_renderer(&params);
    launch(&params);
    return 0;
}

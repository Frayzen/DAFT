#include "../include/image_renderer.h"
#include <stdio.h>
int main(){
    app_params params;
    params.width = 400;
    params.height = 250;
    params.FPS_UPPER_LIMIT=30;
    setup_renderer(&params);
    launch(&params);
    return 0;
}

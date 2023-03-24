#include "../../include/architecture/bbox.h"


void free_bbox(bbox* b){
    if(!b | !b->tris)
        return;
    for(int i = 0; i < b->c_size; i++){
        free_bbox(b->children[i]);
    }
    free(b);
}
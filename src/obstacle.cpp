#include "obstacle.h"

Obstacle::Obstacle(int x, int y, int w, int h){
    rect.x = 20 * x;
    rect.y = 20 * y;
    rect.w = 20 * w;
    rect.h = 20 * h;
}

bool Obstacle::isHere(int x, int y) {
    for (size_t i = 0; i < rect.w; i++) {
        for (size_t j = 0; j < rect.h; j++) {
            if ( (rect.x+i) == 20*x && (rect.y+j) == 20*y ){
                return true;
            }
        }
    }
    return false;
}

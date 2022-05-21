#ifndef OBSTACLE_H
#define OBSTACLE_H

#include <random>
#include <memory>
#include "SDL.h"

class Obstacle
{
public:
    Obstacle(int, int, int, int);
    bool isHere(int, int);
    SDL_Rect rect;

private:

};

#endif

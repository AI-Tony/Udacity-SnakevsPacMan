#ifndef PACMAN_H
#define PACMAN_H

#include <vector>
#include "SDL.h"
#include "SDL_image.h"
#include "obstacle.h"

struct Coordinates {
    int x, y;
};

struct Node {
    Coordinates coordinates;
    int g, h, f;
};

class Pacman {
public:
    Pacman(int grid_width, int grid_height);

    SDL_Surface *surface;

    int getX() const { return _position.x; }
    int getY() const { return _position.y; }

    void setGoal(int x, int y);
    bool PacmanCell(int, int);
    void findPath(const std::vector<Obstacle> &);
    void Update();
    void clean();
    void eaten();

private:
    int _counter{0};
    int _grid_width;
    int _grid_height;
    float _speed{0.1f};
    Coordinates _position;

    Coordinates _goal;
    std::vector<Node> _open;
    std::vector<Coordinates> _closed;
    std::vector<Coordinates> _path;
    std::vector<Coordinates> neighbours { {0,1}, {0,-1}, {1,0}, {-1,0} };
    bool isValid(Coordinates, const std::vector<Obstacle> &);
    int calculateHeuristic(Coordinates);
};

#endif

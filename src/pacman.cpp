#include <iostream>
#include <cmath>
#include <bits/stdc++.h>
#include "pacman.h"

Pacman::Pacman(int grid_width, int grid_height)
    : _grid_width(grid_width),
      _grid_height(grid_height) {
    _position.x = grid_width / 4;
    _position.y = grid_height * 3 / 4;
    surface = IMG_Load("../assets/pacman.bmp");
}

void Pacman::setGoal(int x, int y) {
    _goal.x = x;
    _goal.y = y;
}

void Pacman::Update()
{
    _counter++;
    if ( _counter % (int)(1/_speed) == 0 ) {
        _position = _path.front();
        _path.erase(_path.begin());
    }
}

void Pacman::clean() {
    _open.clear();
    _closed.clear();
    _path.clear();
}

bool Pacman::PacmanCell(int x, int y) {
    if ( x == _position.x && y == _position.y ) {
        return true;
    }
    return false;
}

void Pacman::eaten() {
    _position.x = _grid_width / 4;
    _position.y = _grid_height * 3 / 4;
    clean();
}

int Pacman::calculateHeuristic(Coordinates current)
{
    int x1 = current.x, y1 = current.y;
    int x2 = _goal.x, y2 = _goal.y;
    return std::sqrt( ( x2 - x1 )*( x2 - x1 ) + ( y2 - y1 )*( y2 - y1 ) );
}

bool Pacman::isValid(Coordinates candidate, const std::vector<Obstacle> &obstacles) {
    for ( auto closed : _closed) {
        if ( closed.x == candidate.x && closed.y == candidate.y ) {
            return false;
        }
    }
    for ( auto obstacle : obstacles ) {
        if ( obstacle.isHere(candidate.x, candidate.y) ) {
            return false;
        }
    }
    return true;
}

void Pacman::findPath(const std::vector<Obstacle> &obstacles)
{
    Node start;
    start.coordinates = _position;
    start.g = 0;
    start.h = calculateHeuristic(_position);
    start.f = start.g + start.h;
    _open.push_back(start);
    while ( !_open.empty() ) {
        std::sort(_open.begin(), _open.end(), []( Node n1, Node n2 ) { return n1.f > n2.f; } );
        Node current = _open.back();
        _path.push_back(current.coordinates);
        _open.clear();
        if ( current.coordinates.x == _goal.x && current.coordinates.y == _goal.y ) {
            break;
        } else {
            for ( Coordinates neighbour : neighbours ){
                Coordinates tmp;
                tmp.x = current.coordinates.x + neighbour.x;
                tmp.y = current.coordinates.y + neighbour.y;
                if ( isValid(tmp, obstacles) ) {
                    Node candidate;
                    candidate.coordinates = tmp;
                    candidate.g = current.g + 1;
                    candidate.h = calculateHeuristic(candidate.coordinates);
                    candidate.f = candidate.g + candidate.h;
                    _open.push_back(candidate);
                    _closed.push_back(candidate.coordinates);
                }
            }
        }
    }
}

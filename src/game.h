#ifndef GAME_H
#define GAME_H

#include <random>
#include <memory>
#include "SDL.h"
#include "controller.h"
#include "renderer.h"
#include "snake.h"
#include "pacman.h"
#include "obstacle.h"

class Game {
 public:
  Game(std::size_t grid_width, std::size_t grid_height);
  void Run(Controller const &controller, Renderer &renderer,
           std::size_t target_frame_duration);
  int GetScore() const;
  int GetSize() const;

 private:
  Snake snake;
  Pacman pacman;
  SDL_Point food;
  std::vector<Obstacle> obstacles;
  const int NUMBER_OF_OBSTACLES = 4;
  std::shared_ptr<SDL_Rect[]> obstacleRects{new SDL_Rect[NUMBER_OF_OBSTACLES]};
  // std::shared_ptr<std::vector<Obstacle>> obstacles{new std::vector<Obstacle>[NUMBER_OF_OBSTACLES]};

  std::random_device dev;
  std::mt19937 engine;
  std::uniform_int_distribution<int> random_x;
  std::uniform_int_distribution<int> random_y;
  std::uniform_int_distribution<int> random_w;
  std::uniform_int_distribution<int> random_h;

  int score{0};
  int pacman_score{0};

  void Update();
  void PlaceFood();
  bool ObstacleCell(int, int);
};

#endif

#include "game.h"
#include <iostream>
#include "SDL.h"

Game::Game(std::size_t grid_width, std::size_t grid_height)
    : snake(grid_width, grid_height),
      pacman(grid_width, grid_height),
      engine(dev()),
      random_x(0, static_cast<int>(grid_width - 1)),
      random_y(0, static_cast<int>(grid_height - 1)),
      random_w(1, 6),
      random_h(1, 6) {
  for (size_t i = 0; i < NUMBER_OF_OBSTACLES; i++) {
      obstacles.push_back( Obstacle(random_x(engine), random_y(engine), random_w(engine), random_h(engine)) );
      obstacleRects[i] = obstacles[i].rect;
  }
  PlaceFood();
}

void Game::Run(Controller const &controller, Renderer &renderer,
               std::size_t target_frame_duration) {
  Uint32 title_timestamp = SDL_GetTicks();
  Uint32 frame_start;
  Uint32 frame_end;
  Uint32 frame_duration;
  int frame_count = 0;
  bool running = true;

  while (running) {
    frame_start = SDL_GetTicks();

    // Input, Update, Render - the main game loop.
    controller.HandleInput(running, snake);
    Update();
    renderer.Render(snake, pacman, food, obstacleRects.get());

    frame_end = SDL_GetTicks();

    // Keep track of how long each loop through the input/update/render cycle
    // takes.
    frame_count++;
    frame_duration = frame_end - frame_start;

    // After every second, update the window title.
    if (frame_end - title_timestamp >= 1000) {
      renderer.UpdateWindowTitle(score, frame_count);
      frame_count = 0;
      title_timestamp = frame_end;
    }

    // If the time for this frame is too small (i.e. frame_duration is
    // smaller than the target ms_per_frame), delay the loop to
    // achieve the correct frame rate.
    if (frame_duration < target_frame_duration) {
      SDL_Delay(target_frame_duration - frame_duration);
    }
  }
}

void Game::PlaceFood() {
  int x, y;
  while (true) {
    x = random_x(engine);
    y = random_y(engine);
    // Check that the location is not occupied by a snake item before placing
    // food.
    if ( !snake.SnakeCell(x, y) && !pacman.PacmanCell(x, y) && !ObstacleCell(x, y) ) {
      food.x = x;
      food.y = y;
      pacman.clean();
      pacman.setGoal(x, y);
      pacman.findPath(obstacles);
      return;
    }
  }
}

void Game::Update() {
  if (!snake.alive) return;

  snake.Update();
  pacman.Update();

  int new_x = static_cast<int>(snake.head_x);
  int new_y = static_cast<int>(snake.head_y);

  // Check if there's food over here
  if (food.x == new_x && food.y == new_y) {
    score++;
    PlaceFood();
    // Grow snake and increase speed.
    snake.GrowBody();
    snake.speed += 0.02;
  }

  // checks if pacman gets the food
  if (food.x == pacman.getX() && food.y == pacman.getY()) {
    pacman_score++;
    PlaceFood();
  }

  // checks if snake has eaten pacman
  if (new_x == pacman.getX() && new_y == pacman.getY()) {
      pacman.eaten();
      pacman.findPath(obstacles);
  }

  // checks if snake has crashed into obstacle
  if ( ObstacleCell(new_x, new_y) ) {
      std::cout << "You crashed!" << '\n';
      snake.alive = false;
  }
}

// helper function to cycle trough obstacles and check they don't coinside with other objects
bool Game::ObstacleCell(int x, int y) {
    for ( auto &obstacle : obstacles ) {
        if ( obstacle.isHere(x, y) ) { return true; }
    }
    return false;
}

int Game::GetScore() const { return score; }
int Game::GetSize() const { return snake.size; }

#ifndef RENDERER_H
#define RENDERER_H

#include <vector>
#include <memory>
#include "SDL.h"
#include "snake.h"
#include "pacman.h"

class Renderer {
 public:
  Renderer(const std::size_t screen_width, const std::size_t screen_height,
           const std::size_t grid_width, const std::size_t grid_height);
  ~Renderer();

  void Render(Snake const snake, Pacman pacman, SDL_Point const &food, SDL_Rect const obstacleRects[]);
  void UpdateWindowTitle(int score, int pacman_score, int fps);

 private:
  SDL_Window *sdl_window;
  SDL_Texture *pacmanTexture;
  SDL_Renderer *sdl_renderer;

  const std::size_t screen_width;
  const std::size_t screen_height;
  const std::size_t grid_width;
  const std::size_t grid_height;
};

#endif

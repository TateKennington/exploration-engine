#ifndef LEVEL_H
#define LEVEL_H

#include<vector>
#include "graphics.h"
#include "transform.h"
#include "SDL2/SDL.h"

class Tile{
 public:
  Transform transform;
  Sprite sprite;

  Tile();
  Tile(Transform* _t, Sprite* _s);

  bool collides(Transform* other);
  void render(SDL_Renderer* renderer);
  void nextFrame();
};

class Level{
 public:
  std::vector<Tile> tiles;

  Level();
  Level(std::vector<Tile>* _tiles);

  void render(SDL_Renderer* renderer);
  void update();
  bool collides(Transform* other);
};

#endif

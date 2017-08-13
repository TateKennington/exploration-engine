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

class Warp{
 public:
  Transform transform;
  int dest_level_x, dest_level_y, x, y;

  Warp();
  Warp(Transform* _t, int _dest_level_x, int _dest_level_y, int _x, int _y);

  bool collides(Transform* other);
};

class Level{
 public:
  std::vector<Tile> tiles;
  std::vector<Warp> warps;
  
  Level();
  Level(std::vector<Tile>* _tiles);

  void render(SDL_Renderer* renderer);
  void update();
  bool collides(Transform* other);
  int checkWarp(Transform* other);
};

#endif

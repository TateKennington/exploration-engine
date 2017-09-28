#ifndef LIGHTLEVEL_H_
#define LIGHTLEVEL_H_

#include<SDL2/SDL.h>

class LightLevel{
 public:
  int intensity;
  int base;
  SDL_Texture* texture;
  
  LightLevel();

  void render(SDL_Renderer* renderer, SDL_Rect* temp);
  void bake();
  void reset();
};

#endif

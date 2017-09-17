#ifndef LIGHT_H_
#define LIGHT_H_

#include "SDL2/SDL.h"

class Light{
 public:
  int x, y, z;

  Light();
  Light(int _x, int _y, int _z);

  void setPos(int _x, int _y, int _z);
  
  SDL_Rect castShadow(SDL_Rect src, int srcz, int destz);

};

#endif

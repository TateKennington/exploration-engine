#ifndef LIGHT_H_
#define LIGHT_H_

#include "SDL2/SDL.h"
#include "lightlevel.h"

class Light{
 public:
  int x, y, z, radius;
  SDL_Texture* texture;
  
  Light();
  Light(int _x, int _y, int _z, int _radius);

  void setPos(int _x, int _y, int _z);
  void illuminate(std::vector<std::vector<LightLevel> > *l);
  SDL_Rect castShadow(SDL_Rect src, int srcz, int destz);

};

#endif

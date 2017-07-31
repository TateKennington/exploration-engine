#ifndef TRANSFORM_H
#define TRANSFORM_H

#include<SDL2/SDL.h>

class Transform{
 public:
  float x, y;
  int width, height;
  SDL_Rect constraint;
  
  Transform();
  Transform(float _x, float _y, int _width, int _height);

  void setPosition(float _x, float _y);
  void move(float dx, float dy);
  void constrain(SDL_Rect _c);
  bool collides(Transform other);
  
};

#endif

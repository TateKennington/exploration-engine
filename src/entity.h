#ifndef ENTITY_H
#define ENTITY_H

#include<SDL2/SDL.h>
#include "transform.h"
#include "graphics.h"
#include "physics.h"
#include "light.h"

class Entity{

 public:

  Entity();
  Entity(Transform* _t, Sprite* _s, PhysicsBody* _pBody);
  Transform transform;
  Sprite sprite;
  PhysicsBody pBody;
  
  void render(SDL_Renderer* renderer);
  void renderShadow(SDL_Renderer* renderer, Light l);
};

#endif

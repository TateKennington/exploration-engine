#include "entity.h"
#include<iostream>
Entity::Entity(){
}

Entity::Entity(Transform* _t, Sprite* _s, PhysicsBody* _pBody){
  transform = (*_t);
  sprite = (*_s);
  pBody = (*_pBody);
}

void Entity::render(SDL_Renderer* renderer){
  SDL_Rect rect;
  rect.x = transform.x;
  rect.y = transform.y;
  rect.w = transform.width;
  rect.h = transform.height;
  sprite.render(renderer, &rect);
}

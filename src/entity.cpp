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

void Entity::renderShadow(SDL_Renderer* renderer, Light l){
  SDL_Rect rect;
  rect.x = transform.x;
  rect.y = transform.y;
  rect.w = transform.width;
  rect.h = transform.height;

  SDL_Rect shadow = l.castShadow(rect, 1, 0);

  SDL_SetTextureAlphaMod(sprite.sheet, 0x42);
  SDL_SetTextureColorMod(sprite.sheet, 0x00,0x00,0x00);
  sprite.render(renderer, &shadow);
  SDL_SetTextureAlphaMod(sprite.sheet, 0xFF);
  SDL_SetTextureColorMod(sprite.sheet, 0xFF,0xFF,0xFF);
}

#include "gui.h"

void GUIContainer::render(SDL_Renderer* renderer){
  if(itemType == PANEL){
    GUIPanel temp = (*((GUIPanel*)item));
    temp.render(renderer);
  }else if(itemType == SLIDER){
    GUISlider temp = (*((GUISlider*)item));
    temp.render(renderer);
  }
}

GUIPanel::GUIPanel(std::string _text, Transform* t, SDL_Texture* s){
  text = _text;
  position = (*t);
  background = s;
}

void GUIPanel::render(SDL_Renderer* renderer){
  SDL_Rect temp;
  temp.x = position.x;
  temp.y = position.y;
  temp.w = position.width;
  temp.h = position.height;
  SDL_RenderCopy(renderer, background, NULL, &temp);
}

GUISlider::GUISlider(SDL_Texture* t, Transform* _pos){
  texture = t;
  position = (*_pos);
}

void GUISlider::render(SDL_Renderer* renderer){
  SDL_Rect temp;
  temp.x = position.x;
  temp.y = position.y;
  temp.w = position.width;
  temp.h = position.height;
  SDL_RenderCopy(renderer, texture, NULL, &temp);
}

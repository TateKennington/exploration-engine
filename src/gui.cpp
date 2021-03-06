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

GUIPanel::GUIPanel(std::string _text, Sprite* _font, Transform* t, SDL_Texture* s){
  font = (*_font);
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
  temp.w = temp.w/text.length();
  temp.y = (temp.y+temp.h)/2 - temp.w/2;
  temp.h = temp.w;
  for(int i = 0; i<text.length();i++){
    font.setFrame(text[i]-'a');
    font.render(renderer, &temp);
    temp.x+=temp.w;
  }
}

GUISlider::GUISlider(SDL_Texture* _foreground, SDL_Texture* _background, Transform* _pos, int _max, int _value){
  foreground = _foreground;
  background = _background;
  position = (*_pos);
  max = _max;
  value = _value;
}

void GUISlider::render(SDL_Renderer* renderer){
  SDL_Rect temp;
  temp.x = position.x-5;
  temp.y = position.y-5;
  temp.w = position.width+10;
  temp.h = position.height+10;

  SDL_RenderCopy(renderer, background, NULL, &temp);

  temp.x = position.x;
  temp.y = position.y;
  temp.w = position.width/max;
  temp.h = position.height;
  
  for(int i = 0; i<value; i++){
    SDL_RenderCopy(renderer, foreground, NULL, &temp);
    temp.x+=temp.w;
  }
  
}

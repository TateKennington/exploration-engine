#ifndef GUI_H_
#define GUI_H_

#include "graphics.h"
#include "transform.h"
#include<string>

enum{PANEL, SLIDER};

class GUIContainer{
 public:
  void* item;
  int itemType;

  void render(SDL_Renderer* renderer);
};

class GUIPanel{
 public:
  SDL_Texture* background;
  std::string text;
  Transform position;
  Sprite font;
  
  GUIPanel(std::string _text, Sprite* _font, Transform* t, SDL_Texture* s);
  void render(SDL_Renderer* renderer);
};

class GUISlider{
 public:
  SDL_Texture *foreground, *background;
  Transform position;
  int value, max;
  
  GUISlider(SDL_Texture* foreground, SDL_Texture* _background, Transform* _pos, int _max, int _value);
  void render(SDL_Renderer* renderer);
};

#endif

#ifndef GUI_H_
#define GUI_H_

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

  GUIPanel(std::string _text, Transform* t, SDL_Texture* s);
  void render(SDL_Renderer* renderer);
};

class GUISlider{
 public:
  SDL_Texture* texture;
  Transform position;
  
  GUISlider(SDL_Texture* t, Transform* _pos);
  void render(SDL_Renderer* renderer);
};

#endif

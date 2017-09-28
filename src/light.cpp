#include <string>
#include <vector>
#include <cmath>
#include "light.h"
#include "utils.h"
#include "game.h"

Light::Light(){
  x = 0;
  y = 0;
  z = 0;
  radius = 10;
  texture = loadTexture("light.bmp");
}

Light::Light(int _x, int _y, int _z, int _radius){
  x = _x;
  y = _y;
  z = _z;
  radius = _radius;
  texture = loadTexture("light.bmp");
  SDL_SetTextureColorMod(texture, 0xFF, 0x45, 0x00);
  SDL_SetTextureAlphaMod(texture, 0x42);
}

void Light::setPos(int _x, int _y, int _z){
  x = _x;
  y = _y;
  z = _z;
}

void Light::illuminate(std::vector<std::vector<LightLevel> > *l){
  int w = SCREEN_WIDTH/l->size()+1;
  int h = SCREEN_HEIGHT/(*l)[0].size()+1;

  for(int i = 0; i<l->size(); i++){
	for(int j = 0; j<(*l)[i].size(); j++){
	  int ax = i*w; int ay = j*h;
	  int intensity = 0xFF - sqrt(1+(ax-x+10)*(ax-x+10)+(ay-y+10)*(ay-y+10))/2;
	  (*l)[i][j].intensity += intensity;
	}
  }
 
}

SDL_Rect Light::castShadow(SDL_Rect src, int srcz, int destz){
  SDL_Rect res;

  int xdif = src.x - x;
  int ydif = src.y - y;
  int zdif = z - srcz;
  
  res.x = x + sqrt(((xdif*xdif + zdif*zdif)/(zdif*zdif)-1)*(z - destz)*(z - destz)) * (xdif>0?1:-1);
  xdif+=src.w;
  res.w = abs(res.x - (x + sqrt(((xdif*xdif + zdif*zdif)/(zdif*zdif)-1)*(z - destz)*(z - destz)) * (xdif>0?1:-1)));
  res.y = y + sqrt(((ydif*ydif + zdif*zdif)/(zdif*zdif)-1)*(z - destz)*(z - destz)) * (ydif>0?1:-1);
  ydif+=src.h;
  res.h = abs(res.y - (y + sqrt(((ydif*ydif + zdif*zdif)/(zdif*zdif)-1)*(z - destz)*(z - destz)) * (ydif>0?1:-1)));
  
  return res;
}

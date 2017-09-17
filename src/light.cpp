#include "light.h"

Light::Light(){
  x = 0;
  y = 0;
  z = 0;
}

Light::Light(int _x, int _y, int _z){
  x = _x;
  y = _y;
  z = _z;
}

void Light::setPos(int _x, int _y, int _z){
  x = _x;
  y = _y;
  z = _z;
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

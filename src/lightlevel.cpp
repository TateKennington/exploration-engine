#include <string>
#include "lightlevel.h"
#include "utils.h"

LightLevel::LightLevel(){
  intensity = 0;
  base = 0;
  texture = NULL;
}

void LightLevel::render(SDL_Renderer* renderer, SDL_Rect* temp){
  int threshold = 0x40;
  
  intensity = intensity>0xFF?0xFF:intensity;
  intensity = intensity<0?0:intensity;
  
  if(intensity>=threshold){
    SDL_SetTextureAlphaMod(texture, intensity);
    SDL_SetTextureColorMod(texture, intensity, intensity, intensity);
  }
  else{
    SDL_SetTextureAlphaMod(texture,intensity>threshold-20?intensity:((double)(threshold-intensity)/(threshold)*0xFF));
    SDL_SetTextureColorMod(texture, intensity, intensity, intensity);
  }
  SDL_RenderCopy(renderer, texture, NULL, temp);
}

void LightLevel::bake(){
  base = intensity;
}

void LightLevel::reset(){
  intensity = base;
}

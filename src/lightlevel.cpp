#include <string>
#include "lightlevel.h"
#include "utils.h"

LightLevel::LightLevel(){
  intensity = 0;
  texture = NULL;
}

void LightLevel::render(SDL_Renderer* renderer, SDL_Rect* temp){
  if(intensity>0x20){
	SDL_SetTextureAlphaMod(texture, intensity>0xAA?0xAA:intensity);
	SDL_SetTextureColorMod(texture, 0xFF, 0xFF, 0xFF);
  }
  else{
	SDL_SetTextureAlphaMod(texture, 0x69);
	SDL_SetTextureColorMod(texture, 0,0,0);
  }
  SDL_RenderCopy(renderer, texture, NULL, temp);
}

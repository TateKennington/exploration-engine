#include "game.h"
#include "utils.h"
#include<cmath>

bool init(){
  
  if(SDL_Init(SDL_INIT_VIDEO | SDL_INIT_JOYSTICK) < 0){
    std::clog<<"SDL_Init failed:"<<std::endl;
    std::clog<<SDL_GetError()<<std::endl<<std::endl;
    return false;
  }
  
  window = SDL_CreateWindow("Window", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
			    SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
  if(window == NULL){
    std::clog<<"SDL_CreateWindow failed:"<<std::endl;
    std::clog<<SDL_GetError()<<std::endl<<std::endl;
    return false;
  } 

  windowRenderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_SOFTWARE);
  if(windowRenderer == NULL){
    std::clog<<"Failed to create Renderer:"<<std::endl;
    std::clog<<SDL_GetError()<<std::endl<<std::endl;
    return false;
  }

  SDL_SetRenderDrawColor(windowRenderer, 0xFF, 0xFF, 0xFF, 0xFF);

  lua_global = luaL_newstate();
  luaL_openlibs(lua_global);
  
  if(SDL_NumJoysticks()<1){
    std::clog<<"Could not find joystick"<<std::endl;
    return true;
  }

  controller = SDL_JoystickOpen(0);

  if(controller == NULL){
    std::clog<<"Unable to open joystick"<<std::endl;
    std::clog<<SDL_GetError()<<std::endl<<std::endl;
    return false;
  }
  
  return true;
}

void close(){
  SDL_DestroyWindow(window);
  SDL_DestroyRenderer(windowRenderer);

  if(controller != NULL){
    SDL_JoystickClose(controller);
  }

  lua_close(lua_global);
  
  SDL_Quit();
}

SDL_Texture* loadTexture(std::string fname){

  SDL_Texture* result = NULL;
  SDL_Surface* loaded = SDL_LoadBMP(fname.c_str());
  
  if(loaded == NULL){
    std::clog<<"Failed to load "<<fname<<std::endl;
    std::clog<<SDL_GetError()<<std::endl<<std::endl;
    return NULL;
  }

  SDL_SetColorKey(loaded, SDL_TRUE, SDL_MapRGB(loaded->format, 0x69, 0x00, 0x69));
  
  result = SDL_CreateTextureFromSurface(windowRenderer, loaded);
  SDL_FreeSurface(loaded);
  
  if(result == NULL){
    std::clog<<"Failed to create texture from "<<fname<<std::endl;
    std::clog<<SDL_GetError()<<std::endl<<std::endl;
    return NULL;
  }

  return result;
}

SDL_Rect castShadow(SDL_Rect src, int srcz, int lightx, int lighty, int lightz, int destz){
  SDL_Rect res;

  int xdif = src.x - lightx;
  int ydif = src.y - lighty;
  int zdif = lightz - srcz;

  res.x = lightx + sqrt(((xdif*xdif + zdif*zdif)/(zdif*zdif)-1)*(lightz - destz)*(lightz - destz)) * (xdif>0?1:-1);
  xdif+=src.w;
  res.w = abs(res.x - (lightx + sqrt(((xdif*xdif + zdif*zdif)/(zdif*zdif)-1)*(lightz - destz)*(lightz - destz)) * (xdif>0?1:-1)));
  res.y = lighty + sqrt(((ydif*ydif + zdif*zdif)/(zdif*zdif)-1)*(lightz - destz)*(lightz - destz)) * (ydif>0?1:-1);
  ydif+=src.h;
  res.h = abs(res.y - (lighty + sqrt(((ydif*ydif + zdif*zdif)/(zdif*zdif)-1)*(lightz - destz)*(lightz - destz)) * (ydif>0?1:-1)));
  
  return res;
}

#include "graphics.h"
#include "game.h"
#include <iostream>

Sprite::Sprite(){
  sheet = NULL;
  frameWidth = -1;
  frameHeight = -1;
  sheetWidth = -1;
  sheetHeight = -1;
  currentFrame.x = -1;
  currentFrame.y = -1;
  currentFrame.w = -1;
  currentFrame.h = -1;
}

Sprite::Sprite(std::string fname, int _frameWidth, int _frameHeight){

  SDL_Texture* result = NULL;
  SDL_Surface* loaded = SDL_LoadBMP(fname.c_str());
  
  if(loaded == NULL){
    std::clog<<"Failed to load "<<fname<<std::endl;
    std::clog<<SDL_GetError()<<std::endl<<std::endl;
    return;
  }

  sheetWidth = loaded->w;
  sheetHeight = loaded->h;

  SDL_SetColorKey(loaded, SDL_TRUE, SDL_MapRGB(loaded->format, 0, 255, 255));
  
  result = SDL_CreateTextureFromSurface(windowRenderer, loaded);
  SDL_FreeSurface(loaded);
  
  if(result == NULL){
    std::clog<<"Failed to create texture from "<<fname<<std::endl;
    std::clog<<SDL_GetError()<<std::endl<<std::endl;
    return;
  }
  
  sheet = result;
  frameWidth = _frameWidth;
  frameHeight = _frameHeight;

  currentFrame.x = 0;
  currentFrame.y = 0;
  currentFrame.w = frameWidth;
  currentFrame.h = frameHeight;
}

void Sprite::setFrame(int index){
  int col = sheetWidth/frameWidth;

  std::clog<<col<<" "<<index%col<<" "<<index/col<<std::endl;
  currentFrame.y = index/col * frameHeight;
  currentFrame.x = (index%col) * frameWidth;
}

void Sprite::nextFrame(){
  currentFrame.x+=frameWidth;
  if(currentFrame.x == sheetWidth){
    currentFrame.x = 0;
    currentFrame.y+=frameHeight;
    if(currentFrame.y == sheetHeight){
      currentFrame.y = 0;
    }
  }
}

void Sprite::render(SDL_Renderer* renderer, SDL_Rect* position){
  SDL_RenderCopy(renderer, sheet, &currentFrame, position);
}

ParticleEmitter::ParticleEmitter(){
  particleNumber = 10;
  lifeTime = 10;
  particles = (Particle*)malloc(sizeof(Particle) * particleNumber);
  for(int i = 0; i< particleNumber; i++){
    particles[i] = Particle();
  }
}

ParticleEmitter::ParticleEmitter(int _particleNumber, int _lifeTime, SDL_Rect _spawnArea,SDL_Texture* _texture, SDL_Rect _liveArea){
  xdir = 0;
  ydir = 0;
  liveArea = _liveArea;
  spawnArea = _spawnArea;
  particleNumber = _particleNumber;
  lifeTime = _lifeTime;
  texture = _texture;
  particles = (Particle*)malloc(sizeof(Particle) * particleNumber);
  for(int i = 0; i < particleNumber; i++){
    particles[i] = Particle(spawnArea.x + rand()%spawnArea.w,spawnArea.y + rand()%spawnArea.h,texture);
  }
}

void ParticleEmitter::setDir(float _xdir, float _ydir){
  xdir = _xdir;
  ydir = _ydir;
}

void ParticleEmitter::update(float dt){
  for(int i = 0; i<particleNumber; i++){
    particles[i].update(dt);
	particles[i].x+=dt*xdir;
	particles[i].y+=dt*ydir;
    if(particles[i].age>lifeTime || particles[i].x<liveArea.x || particles[i].y<liveArea.y || particles[i].y>liveArea.y+liveArea.h || particles[i].x>liveArea.x+liveArea.w){
	  particles[i] = Particle(spawnArea.x + rand()%spawnArea.w,spawnArea.y + rand()%spawnArea.h,texture);
	}
  }
}

void ParticleEmitter::render(SDL_Renderer* renderer){
  for(int i = 0; i<particleNumber; i++){
    particles[i].render(renderer);
  }
}

Particle::Particle(){
  x = 0;
  y = 0;
  age = 0;
}

Particle::Particle(float _x, float _y, SDL_Texture* _texture){
  x = _x;
  y = _y;
  texture = _texture;
  age = 0;
}

void Particle::update(float dt){
  age+=dt;
}

void Particle::render(SDL_Renderer* renderer){
  SDL_Rect pos;
  pos.x = x;
  pos.y = y;
  pos.w = 4;
  pos.h = 4;
  SDL_RenderCopy(renderer, texture, NULL, &pos);
}

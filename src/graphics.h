#ifndef GRAPHICS_H
#define GRAPHICS_H

#include <SDL2/SDL.h>
#include <string>
#include "utils.h"

class Sprite{
 public:

  SDL_Texture* sheet;
  SDL_Rect currentFrame;
  int frameWidth, frameHeight, sheetWidth, sheetHeight;

  Sprite();
  Sprite(std::string fname, int _frameWidth, int _frameHeight);

  void nextFrame();
  void setFrame(int index);
  void render(SDL_Renderer* renderer, SDL_Rect* position);
};

class Particle{
 public:

  SDL_Texture* texture;
  float age;
  float x, y;

  Particle();
  Particle(float _x, float _y, SDL_Texture* _texture);

  void update(float dt);
  void render(SDL_Renderer* renderer);
};


class ParticleEmitter{
 public:

  int particleNumber;
  int lifeTime;
  Particle* particles;
  float xdir, ydir;
  SDL_Rect liveArea;
  SDL_Rect spawnArea;
  SDL_Texture* texture;
  
  ParticleEmitter();
  ParticleEmitter(int _particleNumber, int _lifeTime, SDL_Rect _spawnArea, SDL_Texture* _texture, SDL_Rect _lifeArea);

  void setDir(float _xdir, float _ydir);
  void update(float dt);
  void render(SDL_Renderer* renderer);
};

#endif

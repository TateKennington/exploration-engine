#include "level.h"
#include "utils.h"

Tile::Tile(){
  transform = Transform();
  sprite = Sprite();
}

Tile::Tile(Transform* _t, Sprite* _s){
  transform = (*_t);
  sprite = (*_s);
}

bool Tile::collides(Transform* other){
  return transform.collides(*other);
}

void Tile::render(SDL_Renderer* renderer){
  SDL_Rect temp;
  temp.x = transform.x;
  temp.y = transform.y;
  temp.w = transform.width;
  temp.h = transform.height;

  sprite.render(renderer, &temp);
}

void Tile::renderShadow(SDL_Renderer* renderer, Light l){
  SDL_Rect temp;
  temp.x = transform.x;
  temp.y = transform.y;
  temp.w = transform.width;
  temp.h = transform.height;
  

  SDL_Rect shadow = l.castShadow(temp, 1, 0);

  SDL_SetTextureColorMod(sprite.sheet, 0x00, 0x00, 0x00);
  SDL_SetTextureAlphaMod(sprite.sheet, 0x42);
  sprite.render(renderer, &shadow);
  SDL_SetTextureColorMod(sprite.sheet, 0xFF, 0xFF, 0xFF);
  SDL_SetTextureAlphaMod(sprite.sheet, 0xFF);
}

void Tile::nextFrame(){
  sprite.nextFrame();
}

Warp::Warp(){
  dest_level_x = -1;
  dest_level_y = -1;
  x = 0;
  y = 0;
  transform = Transform(0,0,0,0);
}

Warp::Warp(Transform* _t, int _dest_level_x, int _dest_level_y, int _x, int _y){
  transform = (*_t);
  dest_level_x = _dest_level_x;
  dest_level_y = _dest_level_y;
  x = _x;
  y = _y;
}

bool Warp::collides(Transform* other){
  return transform.collides(*other);
}

Level::Level(){
  tiles = std::vector<Tile>();
}

Level::Level(std::vector<Tile>* _tiles, SDL_Texture* _background){
  background = _background;
  tiles = (*_tiles);
}

void Level::render(SDL_Renderer* renderer){
  SDL_RenderCopy(renderer, background, NULL, NULL);
  for(int i = 0; i<lights.size(); i++){
    for(int j = 0; j<tiles.size(); j++){
      tiles[j].renderShadow(renderer, lights[i]);
    }
  }
  
  for(int i = 0; i<tiles.size();i++){
    tiles[i].render(renderer);
  }
  
}

bool Level::collides(Transform* other){
  for(int i = 0; i<tiles.size(); i++){
    if(tiles[i].collides(other)){
      return true;
    }
  }
}

void Level::update(){
  for(int i = 0; i<tiles.size(); i++){
    tiles[i].nextFrame();
  }
}

int Level::checkWarp(Transform* other){
  for(int i = 0; i<warps.size(); i++){
	if(warps[i].collides(other)) return i;
  }
  return -1;
}

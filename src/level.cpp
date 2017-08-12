#include "level.h"

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

void Tile::nextFrame(){
  sprite.nextFrame();
}

Warp::Warp(){
  dest_level = -1;
  x = 0;
  y = 0;
  transform = Transform(0,0,0,0);
}

Warp::Warp(Transform* _t, int _dest_level, int _x, int _y){
  transform = (*_t);
  dest_level = _dest_level;
  x = _x;
  y = _y;
}

bool Warp::collides(Transform* other){
  return transform.collides(*other);
}

Level::Level(){
  tiles = std::vector<Tile>();
}

Level::Level(std::vector<Tile>* _tiles){
  tiles = (*_tiles);
}

void Level::render(SDL_Renderer* renderer){
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

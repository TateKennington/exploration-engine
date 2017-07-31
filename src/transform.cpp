#include "transform.h"
#include <iostream>

Transform::Transform(){
  x = 0;
  y = 0;
  width = 0;
  height = 0;
  constraint.x = -1;
  constraint.y = -1;
  constraint.w = -1;
  constraint.h = -1;
}

Transform::Transform(float _x, float _y, int _width, int _height){
  x = _x;
  y = _y;
  width = _width;
  height = _height;
  constraint.x = -1;
  constraint.y = -1;
  constraint.w = -1;
  constraint.h = -1;
}

void Transform::setPosition(float _x, float _y){
  x = _x;
  y = _y;
}

void Transform::move(float dx, float dy){
  int right = constraint.w, bottom = constraint.h;
  
  x+=dx;
  y+=dy;
  if(constraint.x != -1){
    if(x<constraint.x){
      x = constraint.x;
    }
    right+=constraint.x;
  }
  if(constraint.y != -1){
    if(y<constraint.y) y = constraint.y;
    bottom+=constraint.y;
  }
  if(constraint.w != -1 && x+width>right){
    x = right-width;
  }
  if(constraint.h != -1 && y+height>bottom){
    y = bottom-height;
  }
}

void Transform::constrain(SDL_Rect _c){
  constraint = _c;
}

bool Transform::collides(Transform other){
  if(y+height>other.y && y+height<=other.y+other.height && x+width > other.x && x+height<=other.x+other.width){
    return true;
  }
  if(other.x+other.width>x && other.y+other.height > y && other.x+other.width<=x+width && other.y + other.height <= y+height) return true;
  return false;
}

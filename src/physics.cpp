#include "game.h"
#include "physics.h"
#include<iostream>

PhysicsBody::PhysicsBody(){
  grounded = false;
  velx = 0;
  vely = 0;
}

void PhysicsBody::addForce(float dx, float dy){
  velx+=dx;
  vely+=dy;
}

void PhysicsBody::update(float dt){
  target->move(velx*dt, vely*dt);
  if(target->y+target->height >= SCREEN_HEIGHT){
	grounded = true;
  }
}

Physics::Physics(){
  entities = std::vector<PhysicsBody*>();
  g = 1;
}

Physics::Physics(int _g){
  entities = std::vector<PhysicsBody*>();
  g = _g;
}

Physics::Physics(int _g, int n){
  entities = std::vector<PhysicsBody*>(n);
  g = _g;
}

void Physics::add(PhysicsBody* e){
  entities.push_back(e);
}

void Physics::update(float dt){
  for(int i  = 0; i<entities.size(); i++){
    if(!entities[i]->grounded)entities[i]->addForce(0,dt*g);
    else entities[i]->vely = 0;
  }
  for(int i = 0; i<entities.size();i++){
    for(int j = 0; j<entities.size(); j++){
      if(i!=j&&entities[i]->target->collides(*(entities[j]->target))){
		entities[i]->velx*=-1;
		entities[i]->vely*=-1;
      }
    }
  }
}

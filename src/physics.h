#ifndef PHYSICS_H
#define PHYSICS_H

#include<vector>
#include "transform.h"

class PhysicsBody{

 public:
  Transform* target;
  bool grounded;
  int velx, vely;

  PhysicsBody();
  PhysicsBody(Transform* _t);
  
  void addForce(float dx, float dy);
  void update(float dt);
};

class Physics{
 public:
  Physics();
  Physics(int _g);
  Physics(int _g, int n);
  
  int g;
  std::vector<PhysicsBody*> entities;

  void add(PhysicsBody* e);
  void update(float dt);
};

#endif

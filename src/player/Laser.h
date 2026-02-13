// This file will create the Laser class
#ifndef LASER_H
#define LASER_H

#include <SFML/Graphics.hpp>
#include "GameEntity.h"

using namespace sf;
using namespace std;

class Laser : public GameEntity {
  private:
    // Direction Vector and Movement Speed
      Vector2f direction;
      float movementSpeed;

 public:
    // Object Set up and Bounds Setting
      Laser(float position_x, float position_y, float direction_x, float direction_y, float movement_speed);
    
    // Game Dynamics and Rendering
      void update();
    
    // Data Handling
      ~Laser();
};
#endif

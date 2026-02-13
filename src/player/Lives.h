// This file will create the Lives class
#ifndef LIVES_H
#define LIVES_H

#include <SFML/Graphics.hpp>
#include "GameEntity.h"
#include "Player.h"

using namespace sf;
using namespace std;

class Lives : public GameEntity {
 private:
 float position_x;
 float position_y;
 float spacing;

 public:
    // Object Set up and Bounds Setting
      Lives(float position_x, float position_y, float spacing);
    
    // Game Dynamics and Rendering
      void update(Player* player, Vector2u WindowSize);
    
    // Data Handling
      ~Lives();
};

#endif

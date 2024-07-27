//This file will define variables and functions made in Laser.h
#include "Laser.h"
#include <SFML/Graphics.hpp>
#include "GameEntity.h"

using namespace sf;
using namespace std;


// Create Constructor for Laser
Laser::Laser(float position_x, float position_y, float direction_x, float direction_y, float movement_speed){
  // Set Image
    setImage("Libraries/Images/Laser1.png");

  // Set Position
    body->setPosition(position_x, position_y);

  // Set Direction
    direction.x = direction_x;
    direction.y = direction_y;

  // Set movement speed
    movementSpeed = movement_speed;

  // Set Origin of Laser
    FloatRect bodySize = body->getGlobalBounds();
    body->setOrigin(bodySize.width/2.,bodySize.height/2.);
    width = bodySize.width/2;
    height = bodySize.height/2;

  // Flip the Image to face the correct direction
    if(direction.x > 0){
      body->setScale(0.5,0.5);
    }
    else{
      body->setScale(-0.5,0.5);
    }
}


// Update the Movement of the Bullet
void Laser::update(){
  body->move(movementSpeed*direction);
}


// Deconstructor
Laser::~Laser(){ 
  delete body; 
}

// This file will define variables and functions made in Lives.h
#include "Lives.h"
#include <SFML/Graphics.hpp>
#include "GameEntity.h"
#include "Player.h"

using namespace sf;
using namespace std;


// Create Constructor for Laser
Lives::Lives(float position_x, float position_y, float spacing){
  // Set Image
    setImage("Images/SpaceShip5.png");

  // Scale Image
    body->setScale(0.75,0.75);
    this->position_x = position_x;
    this->position_y = position_y;
    this->spacing = spacing;

  // Set Origin of Lives Image
    FloatRect bodySize = body->getGlobalBounds();
    body->setOrigin(bodySize.width/2.,bodySize.height/2.);
    width = bodySize.width/2;
    height = bodySize.height/2;
}


// Update Movement to Keep Level with PLayer
void Lives::update(Player* player, Vector2u WindowSize){
  // Track While Screen Scrolling
    if(player->get_x() > WindowSize.x*1.5){
      body->setPosition(WindowSize.x + position_x-spacing,position_y);
    }
    else if(player->get_x() < WindowSize.x*-0.5){
      body->setPosition(position_x-WindowSize.x-spacing,position_y);
    }
    else{
      body->setPosition((player->get_x()+(position_x-WindowSize.x/2)-spacing),position_y);
    }
}


// Deconstructor
Lives::~Lives(){ 
}

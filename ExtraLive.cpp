// This file will define variables and functions made in extra lifes.h
#include "ExtraLive.h"
#include <SFML/Graphics.hpp>
using namespace sf;
using namespace std;
// SPECIFIC CONSTRUCTOR
ExtraLive::ExtraLive(float pos_x, float pos_y) : PowerUp() {
  // Set Image of the Body
  setImage("Images/PowerUp_02.png");
  // Set Position
  body->setPosition(pos_x, pos_y);
  // Scale and Set Origion of Body
}
// Implementation of virtual functions
// Movement Function
void ExtraLive::update() { body->move(speed * 0.09, speed * 0.09); }

// effect on player
int ExtraLive::powerUpEffect() {
  AddLive = AddLive + 1;
  return AddLive;
}
// DECONSTRUCTOR
ExtraLive::~ExtraLive() {}

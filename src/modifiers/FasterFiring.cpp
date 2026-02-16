// This file will will define variables and functions made in FasterFiring.h
#include "FasterFiring.h"
#include <SFML/Graphics.hpp>
using namespace sf;
using namespace std;
// SPECIFIC CONSTRUCTOR
FasterFiring::FasterFiring(float pos_x, float pos_y) : PowerUp() {
  // Set Image of the Body
  setImage("Images/PowerUp_01.png");
  // Set Position
  body->setPosition(pos_x, pos_y);
  // Scale and Set Origion of Body
}
// Implementation of virtual functions
// Movement Function
void FasterFiring::update() { body->move(0, speed * 0.09); }

// effect on player
int FasterFiring::powerUpEffect() {
  return 35;
}

// DECONSTRUCTOR
FasterFiring::~FasterFiring() {}

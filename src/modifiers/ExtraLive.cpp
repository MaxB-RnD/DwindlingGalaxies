// ------------------------------------------------------------------------------
// -               V E R S I O N   I D E N T I F I C A T I O N -
// ------------------------------------------------------------------------------
// File:                    %name: ExtraLive.cpp %
// Date Created:            %date_created: Tue Feb 17 18:51:42 2026 %
// CM Version               %version: 2 %
// CM Instance              %instance: 1 %
// Author:                  %created_by: MBusato %
// ------------------------------------------------------------------------------
// -                          D E S C R I P T I O N -
// ------------------------------------------------------------------------------
// Implementation file for the ExtraLive power-up in Dwindling Galaxies.
// Inherits from the PowerUp base class and defines the specific movement 
// logic and the health/life increment effect for the player.
//
// ------------------------------------------------------------------------------
// -                          L I C E N S I N G -
// ------------------------------------------------------------------------------
// Copyright (c) 2024 EastSide Lion Studios. All rights reserved. Use of this
// software is subject to the license terms found in the LICENSE file located in
// the root directory of this repository.
// ------------------------------------------------------------------------------

#include <SFML/Graphics.hpp>

#include "ExtraLive.h"

using namespace sf;
using namespace std;

ExtraLive::ExtraLive(float pos_x, float pos_y) : PowerUp() 
{
  // Set Image of the Body.
  setImage("Images/PowerUp_02.png");
  
  // Set Position.
  body->setPosition(pos_x, pos_y);
  
  // Note: Scale and Origin are Handled by PowerUp/Object Initialisation.
}

ExtraLive::~ExtraLive() 
{
}

void ExtraLive::update() 
{ 
  // Update the Position of the Power-Up Over Time.
  body->move(speed * 0.09f, speed * 0.09f); 
}

int ExtraLive::powerUpEffect() 
{
  // Returns the Value to be Added to the Player's Life Count.
  return 1;
}

// ------------------------------------------------------------------------------
// -               V E R S I O N   I D E N T I F I C A T I O N -
// ------------------------------------------------------------------------------
// File:                    %name: FasterFiring.cpp %
// Date Created:            %date_created: Tue Feb 17 18:58:32 2026 %
// CM Version               %version: 2 %
// CM Instance              %instance: 1 %
// Author:                  %created_by: MBusato %
// ------------------------------------------------------------------------------
// -                          D E S C R I P T I O N -
// ------------------------------------------------------------------------------
// Implementation file for the FasterFiring power-up in Dwindling Galaxies.
// Inherits from the PowerUp base class and defines the specific movement 
// logic and the fire-rate modification effect for the player.
//
// ------------------------------------------------------------------------------
// -                          L I C E N S I N G -
// ------------------------------------------------------------------------------
// Copyright (c) 2024 EastSide Lion Studios. All rights reserved. Use of this
// software is subject to the license terms found in the LICENSE file located in
// the root directory of this repository.
// ------------------------------------------------------------------------------

#include <SFML/Graphics.hpp>

#include "FasterFiring.h"

using namespace sf;
using namespace std;

FasterFiring::FasterFiring(float pos_x, float pos_y) : PowerUp() 
{
  // Set Image of the Body.
  setImage("Images/PowerUp_01.png");

  // Set Position.
  body->setPosition(pos_x, pos_y);

  // Note: Scale and Origin are handled by PowerUp/Object initialisation.
}

FasterFiring::~FasterFiring() 
{
}

void FasterFiring::update() 
{ 
  // Update the Position of the Power-Up Along the Y-axis.
  body->move(0.f, speed * 0.09f); 
}

int FasterFiring::powerUpEffect() 
{
  // Returns the Value to Modify the Player's Firing Rate.
  return 35;
}

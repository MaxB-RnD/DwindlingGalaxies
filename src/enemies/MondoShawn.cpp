// ------------------------------------------------------------------------------
// -               V E R S I O N   I D E N T I F I C A T I O N -
// ------------------------------------------------------------------------------
// File:                    %name: MondoShawn.cpp %
// Date Created:            %date_created: Tue Feb 17 18:16:02 2026 %
// CM Version               %version: 2 %
// CM Instance              %instance: 1 %
// Author:                  %created_by: MBusato %
// ------------------------------------------------------------------------------
// -                          D E S C R I P T I O N -
// ------------------------------------------------------------------------------
// Implementation file for the MondoShawn enemy class in Dwindling Galaxies.
// Inherits from the Alien base class and defines specific movement patterns
// and sprite initialization for this enemy type.
//
// ------------------------------------------------------------------------------
// -                          L I C E N S I N G -
// ------------------------------------------------------------------------------
// Copyright (c) 2024 EastSide Lion Studios. All rights reserved. Use of this
// software is subject to the license terms found in the LICENSE file located in
// the root directory of this repository.
// ------------------------------------------------------------------------------

#include <SFML/Graphics.hpp>

#include "Alien.h"
#include "MondoShawn.h"

using namespace sf;
using namespace std;

MondoShawn::MondoShawn() 
{
}

MondoShawn::MondoShawn(float pos_x, float pos_y) : Alien()
{
  // Set Image of the Body.
  setImage("Images/MondoShawns.png");

  // Set Position.
  body->setPosition(pos_x, pos_y);
}

MondoShawn::~MondoShawn() 
{
}

void MondoShawn::update() 
{
  // Updates the Position of the MondoShawn Sprite.
  body->move(1.f, 2.5f);
}

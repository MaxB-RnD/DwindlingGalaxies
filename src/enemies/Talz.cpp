// ------------------------------------------------------------------------------
// -               V E R S I O N   I D E N T I F I C A T I O N -
// ------------------------------------------------------------------------------
// File:                    %name: Talz.cpp %
// Date Created:            %date_created: Tue Feb 17 18:38:45 2026 %
// CM Version               %version: 2 %
// CM Instance              %instance: 1 %
// Author:                  %created_by: MBusato %
// ------------------------------------------------------------------------------
// -                          D E S C R I P T I O N -
// ------------------------------------------------------------------------------
// Implementation file for the Talz enemy class in Dwindling Galaxies. Inherits 
// from the Alien base class and defines the unique negative-axis movement 
// trajectory for this specific entity.
//
// ------------------------------------------------------------------------------
// -                          L I C E N S I N G -
// ------------------------------------------------------------------------------
// Copyright (c) 2024 EastSide Lion Studios. All rights reserved. Use of this
// software is subject to the license terms found in the LICENSE file located in
// the root directory of this repository.
// ------------------------------------------------------------------------------

#include <iostream>
#include <SFML/Graphics.hpp>

#include "Alien.h"
#include "Talz.h"

using namespace sf;
using namespace std;

Talz::Talz() 
{
}

Talz::Talz(float pos_x, float pos_y) : Alien() 
{
  // Set Image of the Body.
  setImage("Images/Talz.png");

  // Set Position.
  body->setPosition(pos_x, pos_y);
}

Talz::~Talz() 
{
}

void Talz::update() 
{
  // Moves the Talz Entity Along the Specified Vector.
  body->move(-1.5f, -2.5f);
}

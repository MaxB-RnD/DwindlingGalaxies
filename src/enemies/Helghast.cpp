// ------------------------------------------------------------------------------
// -               V E R S I O N   I D E N T I F I C A T I O N -
// ------------------------------------------------------------------------------
// File:                    %name: Helghast.cpp %
// Date Created:            %date_created: Tue Feb 17 18:10:42 2026 %
// CM Version               %version: 2 %
// CM Instance              %instance: 1 %
// Author:                  %created_by: MBusato %
// ------------------------------------------------------------------------------
// -                          D E S C R I P T I O N -
// ------------------------------------------------------------------------------
// Implementation file for the Helghast enemy class in Dwindling Galaxies. It
// inherits from Alien and defines specific movement patterns and asset loading.
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
#include "Helghast.h"

using namespace sf;
using namespace std;

Helghast::Helghast()
{
}

Helghast::Helghast(float pos_x, float pos_y) : Alien()
{
  // Set Image of the Body.
  setImage("Images/Helgahst.png");
  
  // Set Position.
  body->setPosition(pos_x, pos_y);
}

Helghast::~Helghast() 
{
}

void Helghast::update()
{
  body->move(5.f, 1.f);
}

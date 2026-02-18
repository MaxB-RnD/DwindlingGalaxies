// ------------------------------------------------------------------------------
// -               V E R S I O N   I D E N T I F I C A T I O N -
// ------------------------------------------------------------------------------
// File:                    %name: Alien.cpp %
// Date Created:            %date_created: Tue Feb 17 18:12:15 2026 %
// CM Version               %version: 2 %
// CM Instance              %instance: 1 %
// Author:                  %created_by: MBusato %
// ------------------------------------------------------------------------------
// -                          D E S C R I P T I O N -
// ------------------------------------------------------------------------------
// Implementation file for the Alien class in Dwindling Galaxies. It defines 
// functions for alien initialisation, shape handling, and movement dynamics.
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

using namespace sf;
using namespace std;

Alien::Alien()
{
  initShape();
  initVariables();
}  

Alien::Alien(float pos_x, float pos_y) 
{
  // Set Image of the Body.
  setImage("Images/alienShip3.png");
  
  // Set Position.
  body->setPosition(pos_x, pos_y);
  
  // Scale and Set Origin of Body.
  initShape();
  
  // Initialise Variable Values.
  initVariables();
}

Alien::~Alien()
{
}

void Alien::initVariables()
{
  // Initialise Variable Values.
  points = 50;
  speed = 2.5f;
}

void Alien::initShape()
{
  // Set Scale of the Body.
  body->setScale(0.20f, 0.20f);

  // Set Origin of the Body.
  FloatRect bodySize = body->getGlobalBounds();    
  body->setOrigin(bodySize.width / 2.f, bodySize.height / 2.f);

  // Save Values as Width and Height.
  width = bodySize.width / 2.f;
  height = bodySize.height / 2.f;
}

const FloatRect Alien::getBounds() const
{
  return body->getGlobalBounds();
}

const int& Alien::getPoints() const
{
  return points;
}

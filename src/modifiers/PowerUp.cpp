// ------------------------------------------------------------------------------
// -               V E R S I O N   I D E N T I F I C A T I O N -
// ------------------------------------------------------------------------------
// File:                    %name: PowerUp.cpp %
// Date Created:            %date_created: Tue Feb 17 19:01:29 2026 %
// CM Version               %version: 2 %
// CM Instance              %instance: 1 %
// Author:                  %created_by: MBusato %
// ------------------------------------------------------------------------------
// -                          D E S C R I P T I O N -
// ------------------------------------------------------------------------------
// Base implementation file for PowerUp entities in Dwindling Galaxies. It 
// provides core functionality for initialisation, bounding box handling, and 
// speed management that derived power-up classes utilise.
//
// ------------------------------------------------------------------------------
// -                          L I C E N S I N G -
// ------------------------------------------------------------------------------
// Copyright (c) 2024 EastSide Lion Studios. All rights reserved. Use of this
// software is subject to the license terms found in the LICENSE file located in
// the root directory of this repository.
// ------------------------------------------------------------------------------

#include <SFML/Graphics.hpp>

#include "PowerUp.h"

using namespace sf;
using namespace std;

PowerUp::PowerUp()
{
  initShape();
  initVariables();
}

PowerUp::PowerUp(float pos_x, float pos_y) 
{
  // Set Image of the Body.
  setImage("Images/PowerUp_01.png");
    
  // Set Position.
  body->setPosition(pos_x, pos_y);
    
  // Scale and Set Origin of Body.
  initShape();
    
  // Initialize Variable Values.
  initVariables();
}

PowerUp::~PowerUp() 
{
}

void PowerUp::initVariables() 
{
  // Initialise Variable Values.
  points = 25;
  speed = 2.5f;
}

void PowerUp::initShape() 
{
  // Set Scale of the Body.
  body->setScale(0.35f, 0.35f);

  // Set Origin of the Body.
  FloatRect bodySize = body->getGlobalBounds();    
  body->setOrigin(bodySize.width / 2.f, bodySize.height / 2.f);

  // Save Values as Width and Height.
  width = bodySize.width / 2.f;
  height = bodySize.height / 2.f;
}

const FloatRect PowerUp::getBounds() const 
{
  return body->getGlobalBounds();
}

const int& PowerUp::getPoints() const 
{
  return points;
}

void PowerUp::changeSpeed(float new_speed) {
  speed = new_speed;
}

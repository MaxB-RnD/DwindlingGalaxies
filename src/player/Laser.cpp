// ------------------------------------------------------------------------------
// -               V E R S I O N   I D E N T I F I C A T I O N -
// ------------------------------------------------------------------------------
// File:                    %name: Laser.cpp %
// Date Created:            %date_created: Tue Feb 17 19:18:42 2026 %
// CM Version               %version: 2 %
// CM Instance              %instance: 1 %
// Author:                  %created_by: MBusato %
// ------------------------------------------------------------------------------
// -                          D E S C R I P T I O N -
// ------------------------------------------------------------------------------
// Implementation file for the Laser projectile in Dwindling Galaxies. It manages
// bullet initialisation, directional velocity, and sprite orientation
// based on travel direction.
//
// ------------------------------------------------------------------------------
// -                          L I C E N S I N G -
// ------------------------------------------------------------------------------
// Copyright (c) 2024 EastSide Lion Studios. All rights reserved. Use of this
// software is subject to the license terms found in the LICENSE file located in
// the root directory of this repository.
// ------------------------------------------------------------------------------

#include <SFML/Graphics.hpp>

#include "GameEntity.h"
#include "Laser.h"

using namespace sf;
using namespace std;

Laser::Laser(float position_x, float position_y, float direction_x, float direction_y, float movement_speed) 
{
  // Set Image.
  setImage("Images/Laser1.png");

  // Set Position.
  body->setPosition(position_x, position_y);

  // Set Direction.
  direction.x = direction_x;
  direction.y = direction_y;

  // Set Movement Speed.
  movementSpeed = movement_speed;

  // Set Origin of Laser.
  FloatRect bodySize = body->getGlobalBounds();
  body->setOrigin(bodySize.width / 2.f, bodySize.height / 2.f);

  // Save Values as Half-Width and Half-Height.
  width = bodySize.width / 2.f;
  height = bodySize.height / 2.f;

  // Flip the Image to Face the Correct Direction based on X-axis Velocity.
  if (direction.x > 0) 
  {
    body->setScale(0.5f, 0.5f);
  } 
  else 
  {
    body->setScale(-0.5f, 0.5f);
  }
}

Laser::~Laser() 
{ 
}

void Laser::update() 
{
  // Update the Movement of the Bullet.
  body->move(movementSpeed * direction);
}

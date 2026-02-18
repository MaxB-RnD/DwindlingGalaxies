// ------------------------------------------------------------------------------
// -               V E R S I O N   I D E N T I F I C A T I O N -
// ------------------------------------------------------------------------------
// File:                    %name: Lives.cpp %
// Date Created:            %date_created: Tue Feb 17 19:23:45 2026 %
// CM Version               %version: 2 %
// CM Instance              %instance: 1 %
// Author:                  %created_by: MBusato %
// ------------------------------------------------------------------------------
// -                          D E S C R I P T I O N -
// ------------------------------------------------------------------------------
// Implementation file for the Lives UI component in Dwindling Galaxies. It 
// manages the rendering and positioning of life icons, ensuring they 
// remain stationary relative to the player during screen scrolling.
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
#include "Lives.h"
#include "Player.h"

using namespace sf;
using namespace std;

Lives::Lives(float position_x, float position_y, float spacing)
{
  // Set Image.
  setImage("Images/SpaceShip5.png");

  // Scale Image.
  body->setScale(0.75f, 0.75f);
  this->position_x = position_x;
  this->position_y = position_y;
  this->spacing = spacing;

  // Set Origin of Lives Image.
  FloatRect bodySize = body->getGlobalBounds();
  body->setOrigin(bodySize.width / 2.f, bodySize.height / 2.f);
  width = bodySize.width / 2.f;
  height = bodySize.height / 2.f;
}

Lives::~Lives() 
{ 
}

void Lives::update(Player* player, Vector2u WindowSize) 
{
  // Track UI Icons While Screen is Scrolling.
  if (player->get_x() > WindowSize.x * 1.5f) 
  {
    body->setPosition(WindowSize.x + position_x - spacing, position_y);
  } 
  else if (player->get_x() < WindowSize.x * -0.5f) 
  {
    body->setPosition(position_x - WindowSize.x - spacing, position_y);
  } 
  else 
  {
    body->setPosition((player->get_x() + (position_x - WindowSize.x / 2.f) - spacing), position_y);
  }
}

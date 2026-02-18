// ------------------------------------------------------------------------------
// -               V E R S I O N   I D E N T I F I C A T I O N -
// ------------------------------------------------------------------------------
// File:                    %name: GameEntity.cpp %
// Date Created:            %date_created: Tue Feb 17 19:12:32 2026 %
// CM Version               %version: 2 %
// CM Instance              %instance: 1 %
// Author:                  %created_by: MBusato %
// ------------------------------------------------------------------------------
// -                          D E S C R I P T I O N -
// ------------------------------------------------------------------------------
// Base class implementation for all interactive objects in Dwindling Galaxies.
// Handles core SFML rendering, texture loading, and spatial positioning 
// shared by players, enemies, and power-ups.
//
// ------------------------------------------------------------------------------
// -                          L I C E N S I N G -
// ------------------------------------------------------------------------------
// Copyright (c) 2024 EastSide Lion Studios. All rights reserved. Use of this
// software is subject to the license terms found in the LICENSE file located in
// the root directory of this repository.
// ------------------------------------------------------------------------------

#include <iostream>
#include <math.h>
#include <SFML/Graphics.hpp>
#include <string.h>

#include "GameEntity.h"

using namespace sf;
using namespace std;

void GameEntity::setImage(const string picture)
{
  // Check Image Loads Properly.        
  if (!shape.loadFromFile(picture)) 
  {
    cout << picture << " Not Found" << endl;
    exit(0);
  }

  // Set Image as Object.
  body->setTexture(shape);
}

void GameEntity::draw(RenderWindow* win) 
{
  win->draw(*body);
}

int GameEntity::get_x() 
{
  return static_cast<int>(body->getPosition().x);
}

int GameEntity::get_y()
{
  return static_cast<int>(body->getPosition().y);
}

int GameEntity::get_width()
{
  return width;
}

int GameEntity::get_height() 
{
  return height;
}

void GameEntity::set_position(Vector2f position)
{
  body->setPosition(position);
}

const FloatRect GameEntity::getBounds()
{
  return body->getGlobalBounds();
}

void GameEntity::update()
{
  body->move(20.f, 20.f);
}

GameEntity::~GameEntity() 
{
  if (body != nullptr) 
  {
    delete body;
    body = nullptr;
  }
}

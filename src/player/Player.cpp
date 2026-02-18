// ------------------------------------------------------------------------------
// -               V E R S I O N   I D E N T I F I C A T I O N -
// ------------------------------------------------------------------------------
// File:                    %name: Player.cpp %
// Date Created:            %date_created: Tue Feb 17 19:26:55 2026 %
// CM Version               %version: 2 %
// CM Instance              %instance: 1 %
// Author:                  %created_by: MBusato %
// ------------------------------------------------------------------------------
// -                          D E S C R I P T I O N -
// ------------------------------------------------------------------------------
// Implementation file for the Player class in Dwindling Galaxies. It handles 
// player input translation to movement, boundary collision logic, sprite 
// orientation, and state tracking for projectile direction.
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

#include "GameEntity.h"
#include "Player.h"

using namespace sf;
using namespace std;

Player::Player(const string picture, int x, int y) 
{
  // Set Image.
  setImage(picture);
  
  // Set Position.
  body->setPosition(static_cast<float>(x), static_cast<float>(y));
  
  // Scale Image.
  body->setScale(1.f, 1.f);
  
  // Set Origin & Dimensions.
  FloatRect bodySize = body->getGlobalBounds();
  body->setOrigin(bodySize.width / 2.f, bodySize.height / 2.f);
  width = bodySize.width / 2.f;
  height = bodySize.height / 2.f;
}

Player::~Player() 
{
}

bool Player::get_facingDirection() 
{
  return facingDirection;
}

void Player::move_right(int speed, Vector2u WindowSize) 
{
  // Flip the Player and Set Movement Speed.
  body->setScale(-1.f, 1.f);
  body->move(static_cast<float>(speed), 0.f);
  
  // Set Direction for Lasers.
  facingDirection = true;
  
  // Check Screen Boundaries.
  float boundary = (static_cast<float>(WindowSize.x) * 2.f) - width;
  if (body->getPosition().x >= boundary) 
  {
    body->setPosition(boundary, body->getPosition().y);
  }
}

void Player::move_left(int speed, Vector2u WindowSize) 
{
  // Flip the Player and Set Movement Speed.
  body->setScale(1.f, 1.f);
  body->move(static_cast<float>(-speed), 0.f);
  
  // Set Direction for Lasers.
  facingDirection = false;
  
  // Check Screen Boundaries.
  float boundary = width - static_cast<float>(WindowSize.x);
  if (body->getPosition().x <= boundary) 
  {
    body->setPosition(boundary, body->getPosition().y);
  }
}

void Player::move_up(int speed, Vector2u WindowSize) {
  // Set Movement Speed and Direction.
  body->move(0.f, static_cast<float>(-speed));

  // Check Screen Boundaries.
  float boundary = 70.f + height;
  if (body->getPosition().y <= boundary) 
  {
    body->setPosition(body->getPosition().x, boundary);
  }
}

void Player::move_down(int speed, Vector2u WindowSize) {
  // Set Movement Speed and Direction.
  body->move(0.f, static_cast<float>(speed));

  // Check Screen Boundaries.
  float boundary = static_cast<float>(WindowSize.y) - height;
  if (body->getPosition().y >= boundary) {
    body->setPosition(body->getPosition().x, boundary);
  }
}

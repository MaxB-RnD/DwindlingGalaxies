// ------------------------------------------------------------------------------
// -               V E R S I O N   I D E N T I F I C A T I O N -
// ------------------------------------------------------------------------------
// File:                    %name: Player.h %
// Date Created:            %date_created: Tue Feb 17 19:26:55 2026 %
// CM Version               %version: 1 %
// CM Instance              %instance: 1 %
// Author:                  %created_by: MBusato %
// ------------------------------------------------------------------------------
// -                          D E S C R I P T I O N -
// ------------------------------------------------------------------------------
// This file will create the Player class. Represents the player-controlled
// spaceship. Inherits from GameEntity and implements directional movement with
// boundary checking and facing direction tracking for laser firing.
//
// ------------------------------------------------------------------------------
// -                          L I C E N S I N G -
// ------------------------------------------------------------------------------
// Copyright (c) 2024 EastSide Lion Studios. All rights reserved. Use of this
// software is subject to the license terms found in the LICENSE file located in
// the root directory of this repository.
// ------------------------------------------------------------------------------
#ifndef PLAYER_H
#define PLAYER_H

#include <SFML/Graphics.hpp>

#include "GameEntity.h"
#include "Laser.h"

using namespace sf;
using namespace std;

class Player : public GameEntity
{
  public:
    // --------------------------------------------------------------------------
    // DECONSTRUCTOR
    //
    ~Player();

    // --------------------------------------------------------------------------
    // FUNCTION: Player
    //
    // DESCRIPTION:
    //  Initialises the player at the specified position with a sprite image.
    //
    // PARAMETERS:
    //  picture - Filepath to the player sprite image.
    //  x       - Initial X coordinate.
    //  y       - Initial Y coordinate.
    //
    // RETURNS:
    //  None.
    //
    Player(const string picture, int x, int y);

    // --------------------------------------------------------------------------
    // FUNCTION: get_facingDirection
    //
    // DESCRIPTION:
    //  Returns the direction the player is facing (for laser direction).
    //
    // RETURNS:
    //  True if facing right, false if facing left.
    //
    bool get_facingDirection();

    // --------------------------------------------------------------------------
    // FUNCTION: move_right
    //
    // DESCRIPTION:
    //  Moves the player right with boundary checking.
    //
    // PARAMETERS:
    //  speed      - Movement speed.
    //  WindowSize - Window dimensions for boundary checking.
    //
    // RETURNS:
    //  None.
    //
    void move_right(int speed, Vector2u WindowSize);

    // --------------------------------------------------------------------------
    // FUNCTION: move_left
    //
    // DESCRIPTION:
    //  Moves the player left with boundary checking.
    //
    // PARAMETERS:
    //  speed      - Movement speed.
    //  WindowSize - Window dimensions for boundary checking.
    //
    // RETURNS:
    //  None.
    //
    void move_left(int speed, Vector2u WindowSize);

    // --------------------------------------------------------------------------
    // FUNCTION: move_up
    //
    // DESCRIPTION:
    //  Moves the player up with boundary checking.
    //
    // PARAMETERS:
    //  speed      - Movement speed.
    //  WindowSize - Window dimensions for boundary checking.
    //
    // RETURNS:
    //  None.
    //
    void move_up(int speed, Vector2u WindowSize);

    // --------------------------------------------------------------------------
    // FUNCTION: move_down
    //
    // DESCRIPTION:
    //  Moves the player down with boundary checking.
    //
    // PARAMETERS:
    //  speed      - Movement speed.
    //  WindowSize - Window dimensions for boundary checking.
    //
    // RETURNS:
    //  None.
    //
    void move_down(int speed, Vector2u WindowSize);

  private:
    // --------------------------------------------------------------------------
    // Directional Values for Images.
    //
    bool facingDirection;
};

#endif

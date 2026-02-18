// ------------------------------------------------------------------------------
// -               V E R S I O N   I D E N T I F I C A T I O N -
// ------------------------------------------------------------------------------
// File:                    %name: Laser.h %
// Date Created:            %date_created: Tue Feb 17 19:26:55 2026 %
// CM Version               %version: 1 %
// CM Instance              %instance: 1 %
// Author:                  %created_by: MBusato %
// ------------------------------------------------------------------------------
// -                          D E S C R I P T I O N -
// ------------------------------------------------------------------------------
// This file will create the Laser class. Represents projectiles fired by the
// player. Inherits from GameEntity and implements directional movement with
// configurable speed and direction vectors.
//
// ------------------------------------------------------------------------------
// -                          L I C E N S I N G -
// ------------------------------------------------------------------------------
// Copyright (c) 2024 EastSide Lion Studios. All rights reserved. Use of this
// software is subject to the license terms found in the LICENSE file located in
// the root directory of this repository.
// ------------------------------------------------------------------------------
#ifndef LASER_H
#define LASER_H

#include <SFML/Graphics.hpp>

#include "GameEntity.h"

using namespace sf;
using namespace std;

class Laser : public GameEntity
{
  public:
    // --------------------------------------------------------------------------
    // DECONSTRUCTOR
    //
    ~Laser();

    // --------------------------------------------------------------------------
    // FUNCTION: Laser
    //
    // DESCRIPTION:
    //  Initialises a laser projectile at the specified position with direction
    //  and speed.
    //
    // PARAMETERS:
    //  position_x     - Initial X coordinate.
    //  position_y     - Initial Y coordinate.
    //  direction_x    - X component of direction vector.
    //  direction_y    - Y component of direction vector.
    //  movement_speed - Speed multiplier.
    //
    // RETURNS:
    //  None.
    //
    Laser(float position_x, float position_y, float direction_x, float direction_y, float movement_speed);

    // --------------------------------------------------------------------------
    // FUNCTION: update
    //
    // DESCRIPTION:
    //  Updates the laser position according to its direction and speed.
    //
    // RETURNS:
    //  None.
    //
    void update();

  private:
    // --------------------------------------------------------------------------
    // Direction Vector and Movement Speed.
    //
    Vector2f direction;
    float movementSpeed;
};

#endif

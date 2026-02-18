// ------------------------------------------------------------------------------
// -               V E R S I O N   I D E N T I F I C A T I O N -
// ------------------------------------------------------------------------------
// File:                    %name: Lives.h %
// Date Created:            %date_created: Tue Feb 17 19:26:55 2026 %
// CM Version               %version: 1 %
// CM Instance              %instance: 1 %
// Author:                  %created_by: MBusato %
// ------------------------------------------------------------------------------
// -                          D E S C R I P T I O N -
// ------------------------------------------------------------------------------
// This file will create the Lives class. Represents life indicator icons in
// the HUD. Inherits from GameEntity and tracks camera position to remain
// visible during screen scrolling.
//
// ------------------------------------------------------------------------------
// -                          L I C E N S I N G -
// ------------------------------------------------------------------------------
// Copyright (c) 2024 EastSide Lion Studios. All rights reserved. Use of this
// software is subject to the license terms found in the LICENSE file located in
// the root directory of this repository.
// ------------------------------------------------------------------------------
#ifndef LIVES_H
#define LIVES_H

#include <SFML/Graphics.hpp>

#include "GameEntity.h"
#include "Player.h"

using namespace sf;
using namespace std;

class Lives : public GameEntity
{
  public:
    // --------------------------------------------------------------------------
    // DECONSTRUCTOR
    //
    ~Lives();

    // --------------------------------------------------------------------------
    // FUNCTION: Lives
    //
    // DESCRIPTION:
    //  Initialises a life icon at the specified position with horizontal spacing.
    //
    // PARAMETERS:
    //  position_x - Initial X coordinate.
    //  position_y - Initial Y coordinate.
    //  spacing    - Horizontal offset for multiple life icons.
    //
    // RETURNS:
    //  None.
    //
    Lives(float position_x, float position_y, float spacing);

    // --------------------------------------------------------------------------
    // FUNCTION: update
    //
    // DESCRIPTION:
    //  Updates the life icon position to follow camera movement.
    //
    // PARAMETERS:
    //  player     - Pointer to player for camera tracking.
    //  WindowSize - Window dimensions for positioning calculations.
    //
    // RETURNS:
    //  None.
    //
    void update(Player* player, Vector2u WindowSize);

  private:
    // --------------------------------------------------------------------------
    // Position and Spacing.
    //
    float position_x;
    float position_y;
    float spacing;
};

#endif

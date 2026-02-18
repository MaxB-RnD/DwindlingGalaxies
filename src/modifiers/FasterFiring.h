// ------------------------------------------------------------------------------
// -               V E R S I O N   I D E N T I F I C A T I O N -
// ------------------------------------------------------------------------------
// File:                    %name: FasterFiring.h %
// Date Created:            %date_created: Tue Feb 17 19:26:55 2026 %
// CM Version               %version: 1 %
// CM Instance              %instance: 1 %
// Author:                  %created_by: MBusato %
// ------------------------------------------------------------------------------
// -                          D E S C R I P T I O N -
// ------------------------------------------------------------------------------
// Creating file that will create the FasterFiring class. This class inherits
// from the PowerUp base class and grants the player increased firing rate
// when collected. Part of the power-up rotation cycle in gameplay.
//
// ------------------------------------------------------------------------------
// -                          L I C E N S I N G -
// ------------------------------------------------------------------------------
// Copyright (c) 2024 EastSide Lion Studios. All rights reserved. Use of this
// software is subject to the license terms found in the LICENSE file located in
// the root directory of this repository.
// ------------------------------------------------------------------------------
#ifndef FASTERFIRING_H
#define FASTERFIRING_H

#include <SFML/Graphics.hpp>

#include "PowerUp.h"

using namespace sf;
using namespace std;

class FasterFiring : public PowerUp
{
  public:
    // --------------------------------------------------------------------------
    // CONSTRUCTOR
    //
    FasterFiring();

    // --------------------------------------------------------------------------
    // DECONSTRUCTOR
    //
    ~FasterFiring();

    // --------------------------------------------------------------------------
    // FUNCTION: FasterFiring
    //
    // DESCRIPTION:
    //  Initialises a FasterFiring power-up at the specified position.
    //
    // PARAMETERS:
    //  pos_x - Initial X coordinate.
    //  pos_y - Initial Y coordinate.
    //
    // RETURNS:
    //  None.
    //
    FasterFiring(float pos_x, float pos_y);

    // --------------------------------------------------------------------------
    // FUNCTION: powerUpEffect
    //
    // DESCRIPTION:
    //  Returns the effect value for this power-up (number of rapid-fire shots).
    //
    // RETURNS:
    //  Integer effect value.
    //
    int powerUpEffect();

    // --------------------------------------------------------------------------
    // FUNCTION: update
    //
    // DESCRIPTION:
    //  Updates the FasterFiring position according to its movement pattern.
    //
    // RETURNS:
    //  None.
    //
    void update();
};

#endif

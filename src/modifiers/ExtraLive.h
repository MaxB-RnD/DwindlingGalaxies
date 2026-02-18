// ------------------------------------------------------------------------------
// -               V E R S I O N   I D E N T I F I C A T I O N -
// ------------------------------------------------------------------------------
// File:                    %name: ExtraLive.h %
// Date Created:            %date_created: Tue Feb 17 19:26:55 2026 %
// CM Version               %version: 1 %
// CM Instance              %instance: 1 %
// Author:                  %created_by: MBusato %
// ------------------------------------------------------------------------------
// -                          D E S C R I P T I O N -
// ------------------------------------------------------------------------------
// This file will create the ExtraLive class. This class inherits from the
// PowerUp base class and grants the player an additional life when collected.
// Part of the power-up rotation cycle in gameplay.
//
// ------------------------------------------------------------------------------
// -                          L I C E N S I N G -
// ------------------------------------------------------------------------------
// Copyright (c) 2024 EastSide Lion Studios. All rights reserved. Use of this
// software is subject to the license terms found in the LICENSE file located in
// the root directory of this repository.
// ------------------------------------------------------------------------------
#ifndef EXTRALIVE_H
#define EXTRALIVE_H

#include <SFML/Graphics.hpp>

#include "PowerUp.h"

using namespace sf;
using namespace std;

class ExtraLive : public PowerUp
{
  public:
    // --------------------------------------------------------------------------
    // CONSTRUCTOR
    //
    ExtraLive();

    // --------------------------------------------------------------------------
    // DECONSTRUCTOR
    //
    ~ExtraLive();

    // --------------------------------------------------------------------------
    // FUNCTION: ExtraLive
    //
    // DESCRIPTION:
    //  Initialises an ExtraLive power-up at the specified position.
    //
    // PARAMETERS:
    //  pos_x - Initial X coordinate.
    //  pos_y - Initial Y coordinate.
    //
    // RETURNS:
    //  None.
    //
    ExtraLive(float pos_x, float pos_y);

    // --------------------------------------------------------------------------
    // FUNCTION: powerUpEffect
    //
    // DESCRIPTION:
    //  Returns the effect value for this power-up (1 for extra life).
    //
    // RETURNS:
    //  Integer effect value.
    //
    int powerUpEffect();

    // --------------------------------------------------------------------------
    // FUNCTION: update
    //
    // DESCRIPTION:
    //  Updates the ExtraLive position according to its movement pattern.
    //
    // RETURNS:
    //  None.
    //
    void update();
};

#endif

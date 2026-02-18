// ------------------------------------------------------------------------------
// -               V E R S I O N   I D E N T I F I C A T I O N -
// ------------------------------------------------------------------------------
// File:                    %name: MondoShawn.h %
// Date Created:            %date_created: Tue Feb 17 19:26:55 2026 %
// CM Version               %version: 1 %
// CM Instance              %instance: 1 %
// Author:                  %created_by: MBusato %
// ------------------------------------------------------------------------------
// -                          D E S C R I P T I O N -
// ------------------------------------------------------------------------------
// Definition of the MondoShawn enemy type. This class inherits from the Alien 
// base class and implements a specific downward movement pattern. Part of the 
// three-enemy rotation cycle in gameplay.
//
// ------------------------------------------------------------------------------
// -                          L I C E N S I N G -
// ------------------------------------------------------------------------------
// Copyright (c) 2024 EastSide Lion Studios. All rights reserved. Use of this
// software is subject to the license terms found in the LICENSE file located in
// the root directory of this repository.
// ------------------------------------------------------------------------------
#ifndef MONDOSHAWN_H
#define MONDOSHAWN_H

#include <SFML/Graphics.hpp>

#include "Alien.h"

using namespace sf;
using namespace std;

class MondoShawn : public Alien
{
  public:
    // --------------------------------------------------------------------------
    // CONSTRUCTOR
    //
    MondoShawn();

    // --------------------------------------------------------------------------
    // DECONSTRUCTOR
    //
    ~MondoShawn();

    // --------------------------------------------------------------------------
    // FUNCTION: MondoShawn
    //
    // DESCRIPTION:
    //  Initialises a MondoShawn enemy at the specified position.
    //
    // PARAMETERS:
    //  pos_x - Initial X coordinate.
    //  pos_y - Initial Y coordinate.
    //
    // RETURNS:
    //  None.
    //
    MondoShawn(float pos_x, float pos_y);

    // --------------------------------------------------------------------------
    // FUNCTION: update
    //
    // DESCRIPTION:
    //  Updates the MondoShawn position according to its movement pattern.
    //
    // RETURNS:
    //  None.
    //
    void update();
};

#endif

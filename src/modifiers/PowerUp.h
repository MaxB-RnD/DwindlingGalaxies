// ------------------------------------------------------------------------------
// -               V E R S I O N   I D E N T I F I C A T I O N -
// ------------------------------------------------------------------------------
// File:                    %name: PowerUp.h %
// Date Created:            %date_created: Tue Feb 17 19:26:55 2026 %
// CM Version               %version: 1 %
// CM Instance              %instance: 1 %
// Author:                  %created_by: MBusato %
// ------------------------------------------------------------------------------
// -                          D E S C R I P T I O N -
// ------------------------------------------------------------------------------
// This file will create the PowerUp class. Base class for all power-up types
// in Dwindling Galaxies. Provides common movement, scoring, and collision
// detection functionality. Derived classes (FasterFiring, ExtraLive) override
// the update() and powerUpEffect() methods to define specific behaviour.
//
// ------------------------------------------------------------------------------
// -                          L I C E N S I N G -
// ------------------------------------------------------------------------------
// Copyright (c) 2024 EastSide Lion Studios. All rights reserved. Use of this
// software is subject to the license terms found in the LICENSE file located in
// the root directory of this repository.
// ------------------------------------------------------------------------------
#ifndef POWERUP_H
#define POWERUP_H

#include <SFML/Graphics.hpp>

#include "GameEntity.h"

using namespace sf;
using namespace std;

class PowerUp : public GameEntity
{
  public:
    // --------------------------------------------------------------------------
    // CONSTRUCTOR
    //
    PowerUp();

    // --------------------------------------------------------------------------
    // DECONSTRUCTOR
    //
    virtual ~PowerUp();

    // --------------------------------------------------------------------------
    // FUNCTION: PowerUp
    //
    // DESCRIPTION:
    //  Initialises a power-up at the specified position.
    //
    // PARAMETERS:
    //  pos_x - Initial X coordinate.
    //  pos_y - Initial Y coordinate.
    //
    // RETURNS:
    //  None.
    //
    PowerUp(float pos_x, float pos_y);

    // --------------------------------------------------------------------------
    // FUNCTION: update
    //
    // DESCRIPTION:
    //  Pure virtual function for updating power-up position and behaviour.
    //  Must be overridden by derived classes to define specific movement patterns.
    //
    // RETURNS:
    //  None.
    //
    virtual void update() = 0;

    // --------------------------------------------------------------------------
    // FUNCTION: powerUpEffect
    //
    // DESCRIPTION:
    //  Pure virtual function that returns the effect value of this power-up.
    //  Must be overridden by derived classes to define specific effects.
    //
    // RETURNS:
    //  Integer effect value.
    //
    virtual int powerUpEffect() = 0;

    // --------------------------------------------------------------------------
    // FUNCTION: getBounds
    //
    // DESCRIPTION:
    //  Returns the bounding rectangle for collision detection.
    //
    // RETURNS:
    //  FloatRect representing the power-up's collision bounds.
    //
    const FloatRect getBounds() const;

    // --------------------------------------------------------------------------
    // FUNCTION: getPoints
    //
    // DESCRIPTION:
    //  Returns the point value awarded for collecting this power-up.
    //
    // RETURNS:
    //  Integer point value.
    //
    const int& getPoints() const;

    // --------------------------------------------------------------------------
    // FUNCTION: changeSpeed
    //
    // DESCRIPTION:
    //  Modifies the movement speed of this power-up.
    //
    // PARAMETERS:
    //  new_speed - New speed value.
    //
    // RETURNS:
    //  None.
    //
    void changeSpeed(float new_speed);

  protected:
    // --------------------------------------------------------------------------
    // Movement Properties.
    //
    float speed;
    int points;

    // --------------------------------------------------------------------------
    // FUNCTION: initVariables
    //
    // DESCRIPTION:
    //  Initialises movement speed and point values.
    //
    // RETURNS:
    //  None.
    //
    void initVariables();

    // --------------------------------------------------------------------------
    // FUNCTION: initShape
    //
    // DESCRIPTION:
    //  Initialises the sprite and texture for this power-up.
    //
    // RETURNS:
    //  None.
    //
    void initShape();
};

#endif

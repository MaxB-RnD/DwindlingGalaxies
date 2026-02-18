// ------------------------------------------------------------------------------
// -               V E R S I O N   I D E N T I F I C A T I O N -
// ------------------------------------------------------------------------------
// File:                    %name: Alien.h %
// Date Created:            %date_created: Tue Feb 17 19:26:55 2026 %
// CM Version               %version: 1 %
// CM Instance              %instance: 1 %
// Author:                  %created_by: MBusato %
// ------------------------------------------------------------------------------
// -                          D E S C R I P T I O N -
// ------------------------------------------------------------------------------
// Base class for all alien enemy types in Dwindling Galaxies. This class
// provides common movement, scoring, and collision detection functionality.
// Derived classes (Talz, Helghast, MondoShawn) override the update() method
// to define specific movement patterns.
//
// ------------------------------------------------------------------------------
// -                          L I C E N S I N G -
// ------------------------------------------------------------------------------
// Copyright (c) 2024 EastSide Lion Studios. All rights reserved. Use of this
// software is subject to the license terms found in the LICENSE file located in
// the root directory of this repository.
// ------------------------------------------------------------------------------
#ifndef ALIEN_H
#define ALIEN_H

#include <SFML/Graphics.hpp>

#include "GameEntity.h"

using namespace sf;
using namespace std;

class Alien : public GameEntity
{
  public:
    // --------------------------------------------------------------------------
    // CONSTRUCTOR
    //
    Alien();

    // --------------------------------------------------------------------------
    // DECONSTRUCTOR
    //
    virtual ~Alien();

    // --------------------------------------------------------------------------
    // FUNCTION: Alien
    //
    // DESCRIPTION:
    //  Initialises an alien at the specified position.
    //
    // PARAMETERS:
    //  pos_x - Initial X coordinate.
    //  pos_y - Initial Y coordinate.
    //
    // RETURNS:
    //  None.
    //
    Alien(float pos_x, float pos_y);

    // --------------------------------------------------------------------------
    // FUNCTION: update
    //
    // DESCRIPTION:
    //  Pure virtual function for updating alien position and behavior.
    //  Must be overridden by derived classes to define specific movement patterns.
    //
    // RETURNS:
    //  None.
    //
    virtual void update() = 0;

    // --------------------------------------------------------------------------
    // FUNCTION: getPoints
    //
    // DESCRIPTION:
    //  Returns the point value awarded for destroying this alien.
    //
    // RETURNS:
    //  Integer point value.
    //
    const int& getPoints() const;

    // --------------------------------------------------------------------------
    // FUNCTION: getBounds
    //
    // DESCRIPTION:
    //  Returns the bounding rectangle for collision detection.
    //
    // RETURNS:
    //  FloatRect representing the alien's collision bounds.
    //
    const FloatRect getBounds() const;

  private:
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
    //  Initialises the sprite and texture for this alien.
    //
    // RETURNS:
    //  None.
    //
    void initShape();
};

#endif

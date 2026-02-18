// ------------------------------------------------------------------------------
// -               V E R S I O N   I D E N T I F I C A T I O N -
// ------------------------------------------------------------------------------
// File:                    %name: GameEntity.h %
// Date Created:            %date_created: Tue Feb 17 19:26:55 2026 %
// CM Version               %version: 1 %
// CM Instance              %instance: 1 %
// Author:                  %created_by: MBusato %
// ------------------------------------------------------------------------------
// -                          D E S C R I P T I O N -
// ------------------------------------------------------------------------------
// This file will create the GameEntity class. Base class for all game objects
// that require sprites, textures, positioning, collision detection, and
// rendering. Provides common functionality inherited by Player, Alien, PowerUp,
// Laser, and Lives classes.
//
// ------------------------------------------------------------------------------
// -                          L I C E N S I N G -
// ------------------------------------------------------------------------------
// Copyright (c) 2024 EastSide Lion Studios. All rights reserved. Use of this
// software is subject to the license terms found in the LICENSE file located in
// the root directory of this repository.
// ------------------------------------------------------------------------------
#ifndef GAMEENTITY_H
#define GAMEENTITY_H

#include <SFML/Graphics.hpp>
#include <string.h>

using namespace sf;
using namespace std;

class GameEntity
{
  public:
    // --------------------------------------------------------------------------
    // DECONSTRUCTOR
    //
    virtual ~GameEntity();

    // --------------------------------------------------------------------------
    // FUNCTION: setImage
    //
    // DESCRIPTION:
    //  Loads a texture from file and applies it to the sprite.
    //
    // PARAMETERS:
    //  picture - Filepath to the image.
    //
    // RETURNS:
    //  None.
    //
    void setImage(const string picture);

    // --------------------------------------------------------------------------
    // FUNCTION: draw
    //
    // DESCRIPTION:
    //  Renders the entity sprite to the window.
    //
    // PARAMETERS:
    //  win - Pointer to the render window.
    //
    // RETURNS:
    //  None.
    //
    void draw(RenderWindow* win);

    // --------------------------------------------------------------------------
    // FUNCTION: get_x
    //
    // DESCRIPTION:
    //  Returns the X coordinate of the entity.
    //
    // RETURNS:
    //  Integer X position.
    //
    int get_x();

    // --------------------------------------------------------------------------
    // FUNCTION: get_y
    //
    // DESCRIPTION:
    //  Returns the Y coordinate of the entity.
    //
    // RETURNS:
    //  Integer Y position.
    //
    int get_y();

    // --------------------------------------------------------------------------
    // FUNCTION: get_width
    //
    // DESCRIPTION:
    //  Returns the width of the entity sprite.
    //
    // RETURNS:
    //  Integer width.
    //
    int get_width();

    // --------------------------------------------------------------------------
    // FUNCTION: get_height
    //
    // DESCRIPTION:
    //  Returns the height of the entity sprite.
    //
    // RETURNS:
    //  Integer height.
    //
    int get_height();

    // --------------------------------------------------------------------------
    // FUNCTION: set_position
    //
    // DESCRIPTION:
    //  Sets the entity position to the specified coordinates.
    //
    // PARAMETERS:
    //  position - 2D vector containing X and Y coordinates.
    //
    // RETURNS:
    //  None.
    //
    void set_position(Vector2f position);

    // --------------------------------------------------------------------------
    // FUNCTION: getBounds
    //
    // DESCRIPTION:
    //  Returns the bounding rectangle for collision detection.
    //
    // RETURNS:
    //  FloatRect representing the entity's collision bounds.
    //
    const FloatRect getBounds();

    // --------------------------------------------------------------------------
    // FUNCTION: update
    //
    // DESCRIPTION:
    //  Virtual function for updating entity state. Override in derived classes.
    //
    // RETURNS:
    //  None.
    //
    virtual void update();

  protected:
    // --------------------------------------------------------------------------
    // Body Creation for all Inherited Objects.
    //
    Texture shape;
    Sprite* body = new Sprite;

    // --------------------------------------------------------------------------
    // Size Parameters.
    //
    int width;
    int height;
};

#endif

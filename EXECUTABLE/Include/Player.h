// This file will create the Player class
#ifndef PLAYER_H
#define PLAYER_H

#include <SFML/Graphics.hpp>
#include "GameEntity.h"
#include "Laser.h"

using namespace sf;
using namespace std;

class Player: public GameEntity{
    private:
        // Directional values for images
            bool facingDirection;
    public:
        // Setting Values and Rendering Functions
            Player(const string picture, int x, int y);
            bool get_facingDirection();
        
        // Movement Functions
            void move_right(int speed, Vector2u WindowSize);
            void move_left(int speed, Vector2u WindowSize);
            void move_up(int speed, Vector2u WindowSize);
            void move_down(int speed, Vector2u WindowSize);

        // Game Dynamics and Data Handling
            ~Player();
};
#endif

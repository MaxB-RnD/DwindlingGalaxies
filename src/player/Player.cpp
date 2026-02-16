// This file will define the variables and functions made in the Player.h file
#include <SFML/Graphics.hpp>
#include <iostream>
#include "GameEntity.h"
#include "Player.h"

using namespace sf;
using namespace std;

// IMAGE SETTING & RENDERING
    // Constructor for Player
    Player::Player(const string picture, int x, int y){
        // Set Image
            setImage(picture);

        // Set Position
            body->setPosition(x,y);

        // Scale Image
        body->setScale(Vector2f(1, 1));

        //Set Origin & Depth
            FloatRect bodySize = body->getGlobalBounds();
            body->setOrigin(bodySize.width/2.,bodySize.height/2.);
            width = bodySize.width/2;
            height = bodySize.height/2;
    }

    // Return the direction the player is facing
    bool Player::get_facingDirection(){
        return facingDirection;
    }



// MOVEMENT FUNCTIONS
    void Player::move_right(int speed, Vector2u WindowSize){
        // Flip the Player and Set movement Speed
            body->setScale(-1, 1);
            body-> move(speed,0);

        //Set direction for lasers
            facingDirection = true;

        // Check screen boundaries
            int boundary = (WindowSize.x*2) - width;
            if(body->getPosition().x >= boundary){
                body->setPosition(boundary,body->getPosition().y);
            }
    }

    void Player::move_left(int speed, Vector2u WindowSize){
        // Flip the Player and Set movement Speed
            body->setScale(1, 1);
            body-> move(-speed,0);

        //Set direction for lasers
            facingDirection = false;

        // Check screen boundaries
            int boundary = width - WindowSize.x;
            if(body->getPosition().x <= boundary){
                body->setPosition(boundary,body->getPosition().y);
            }

        return;
    }

    void Player::move_up(int speed, Vector2u WindowSize){
        // Set movement speed and direction
            body-> move(0,-speed);
        
        // Check screen boundaries
            int boundary = 70 + height;
            if(body->getPosition().y <= boundary){
                body->setPosition(body->getPosition().x,boundary);
            }
        
        return;
    }

    void Player::move_down(int speed, Vector2u WindowSize){
        // Set movement speed and direction
            body-> move(0,speed);

        // Check screen boundaries
            int boundary = WindowSize.y - height;
            if(body->getPosition().y >= boundary){
                body->setPosition(body->getPosition().x,boundary);
            }

        return;
    }



// GAME DYNAMICS & DATA HANDLING
    // Deconstuctor
    Player::~Player(){
    }
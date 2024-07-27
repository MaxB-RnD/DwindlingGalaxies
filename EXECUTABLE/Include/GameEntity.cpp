// This file will define variables and functions made in GameEntity.h
#include <SFML/Graphics.hpp>
#include <string.h>
#include <math.h>
#include <iostream>

#include "GameEntity.h"

using namespace sf;
using namespace std;

// IMAGE SETTING & RENDERING
    //Set body to image
    void GameEntity::setImage(const string picture){
        // Check image loads properly        
            if(!shape.loadFromFile(picture)){
                cout << picture << " Not Found" << endl;
                exit(0);
            }

        //Set Image as Object
            body->setTexture(shape);
    }

    // Draw Body
    void GameEntity::draw(RenderWindow* win){
        win -> draw(*body);
    }



// POSITION FUNCTIONS
    // Get Position Functions
    int GameEntity::get_x(){
        return body->getPosition().x;
    }
    int GameEntity::get_y(){
        return body->getPosition().y;
    }
    int GameEntity::get_width(){
        return width;
    }
    int GameEntity::get_height(){
        return height;
    }
        
    // Set position of Body
    void GameEntity::set_position(Vector2f position){
        body->setPosition(position);
    }


// GAME DYNAMICS & DATA HANDELING
    // Return Bounds of the Body Object
    const FloatRect GameEntity::getBounds(){
        return body->getGlobalBounds();
    }

    // Update Movement Function
    void GameEntity::update(){
        body->move(20,20);
    }

    //Deconstructor
    GameEntity::~GameEntity(){
        delete body;
    }

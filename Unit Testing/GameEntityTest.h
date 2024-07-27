// This file will conduct unit tests for functions unique to the GameEntity class
#include <iostream>
#include "GameEntity.h"


class GameEntityTest

 {
public:
    void runPositionTests() {
        testGetPosition();
        testSetPosition();
        testUpdate();
        testGetBounds();
    }
private:
    void testGetPosition() {
        // Create an instance of the GameEntity class
            GameEntity entity;
        // Set the position of the entity
            entity.set_position(sf::Vector2f(100.f, 200.f));
        // Get the position values
            int x = entity.get_x();
            int y = entity.get_y();
        // Check if the values are as expected
            if (x != 100 || y != 200) {
                std::cout << "getPosition() test failed!" << std::endl;
            } else {
                std::cout << "getPosition() test passed!" << std::endl;
            }
    }

    void testSetPosition() {
        // Create an instance of the GameEntity class
            GameEntity entity;
        // Set the position of the entity
            entity.set_position(sf::Vector2f(300.f, 400.f));
        // Get the position values
            int x = entity.get_x();
            int y = entity.get_y();
        // Check if the values are as expected
            if (x != 300 || y != 400) {
                std::cout << "setPosition() test failed!" << std::endl;
            } else {
                std::cout << "setPosition() test passed!" << std::endl;
            }
    }
    
    void testUpdate() {
        // Create an instance of the GameEntity class
            GameEntity entity;
        // Set the initial position of the entity
            entity.set_position(sf::Vector2f(100.f, 100.f));
        // Call the update method
            entity.update();
        // Get the updated position values
            int x = entity.get_x();
            int y = entity.get_y();
        // Check if the values are as expected after the update
            if (x != 120 || y != 120) {
                std::cout << "update() test failed!" << std::endl;
            } else {
                std::cout << "update() test passed!" << std::endl;
            }
    }

    void testGetBounds() {
        // Create an instance of the GameEntity class
            GameEntity entity;
        // Set the position of the entity
            entity.set_position(sf::Vector2f(200.f, 200.f));
        // Get the bounds of the entity
            sf::FloatRect bounds = entity.getBounds();
        // Check if the values are as expected
            if (bounds.left != 200.f || bounds.top != 200.f || bounds.width != 0.f || bounds.height != 0.f) {
                std::cout << "getBounds() test failed!" << std::endl;
            } else {
                std::cout << "getBounds() test passed!" << std::endl;
            }
    }
};

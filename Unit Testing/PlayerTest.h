// this class will test functions in the player class
#include <iostream>
#include "Player.h"
class PlayerTest {
public:
    void runTests() {
        testMoveRight();
        testMoveLeft();
        testMoveUp();
        testMoveDown();
        testIsHit();
    }
private:


// this test sees if the moveright function works as intended and will interact with the users keyboard    
    void testMoveRight() {
        Player player("Images/SpaceShip.png", 0, 0);
        Vector2u windowSize(800, 600);
        // Set the initial position of the player
        player.set_position(Vector2f(100.f, 100.f));
        // Move the player to the right with a speed of 5
        player.move_right(5, windowSize);
        // Check if the player's position has changed correctly
        int x = player.get_x();
        if (x != 105) {
            std::cout << "move_right() test failed!" << std::endl;
        } else {
            std::cout << "move_right() test passed!" << std::endl;
        }
    }
// this test sees if the moveleft function works as intended and will interact with the users keyboard
    void testMoveLeft() {
        // Create an instance of the Player class
        Player player("Images/SpaceShip.png", 100, 100);
        // Perform a left movement
        player.move_left(10, sf::Vector2u(800, 600));
        // Get the new position
        int x = player.get_x();
        int y = player.get_y();
        // Check if the position has changed correctly
        if (x != 90 || y != 100) {
            std::cout << "MoveLeft test failed!" << std::endl;
        } else {
            std::cout << "MoveLeft test passed!" << std::endl;
        }
    }
// this test sees if the moveup function works as intended and will interact with the users keyboard
    void testMoveUp() {
        // Create an instance of the Player class
        Player player("Images/SpaceShip.png", 100, 100);
        // Perform an up movement
        player.move_up(10, sf::Vector2u(800, 600));
        // Get the new position
        int x = player.get_x();
        int y = player.get_y();
        // Check if the position has changed correctly
        if (x != 100 || y != 90) {
            std::cout << "MoveUp test failed!" << std::endl;
        } else {
            std::cout << "MoveUp test passed!" << std::endl;
        }
    }
// this test sees if the movedown function works as intended and will interact with the users keyboard
    void testMoveDown() {
        // Create an instance of the Player class
        Player player("Images/SpaceShip.png", 100, 100);
        // Perform a down movement
        player.move_down(10, sf::Vector2u(800, 600));
        // Get the new position
        int x = player.get_x();
        int y = player.get_y();
        // Check if the position has changed correctly
        if (x != 100 || y != 110) {
            std::cout << "MoveDown test failed!" << std::endl;
        } else {
            std::cout << "MoveDown test passed!" << std::endl;
        }
    }

// this test sees if the isHit function works as intended
       void testIsHit() {
        Player player("Images/SpaceShip.png", 0, 0);
        player.set_position(Vector2f(100.f, 100.f));
        // Set a target position and depth
        int targetX = 110;
        int targetY = 110;
        int targetDepth = 10;
        // Check if the player is within the target area
        bool isHit = player.isHit(targetX, targetY, targetDepth);
        if (!isHit) {
            std::cout << "isHit() test failed!" << std::endl;
        } else {
            std::cout << "isHit() test passed!" << std::endl;
        }
    }
};

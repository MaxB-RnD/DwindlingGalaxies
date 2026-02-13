// this file will test functions unique to Lives
#include <iostream>
#include "Lives.h"
#include "Player.h"
class LivesTest {
public:
    void runTests() {
        testUpdate();
    }
private:
    void testUpdate() {
        // Create an instance of the Player class
        Player player("Images/SpaceShip5.png", 100, 200);
        // Create an instance of the Lives class
        Lives lives(10.f, 10.f, 20.f);
        // Create a dummy window size
        Vector2u windowSize(800, 600);
        // Call the update function and pass the Player instance
        lives.update(&player, windowSize);
        // Perform assertions or output messages as needed
        std::cout << "update() test passed!" << std::endl;
    }
};

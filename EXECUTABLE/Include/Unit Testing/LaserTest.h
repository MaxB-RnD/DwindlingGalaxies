// this file will do unit testing for the laser file to ensure it is working
#include <iostream>
#include "Laser.h"
class LaserTest {
public:
    void runTests() {
        testConstructor();
        
    }
private:
    void testConstructor() {
        // Set up test parameters
        float position_x = 100.f;
        float position_y = 200.f;
        float direction_x = 1.f;
        float direction_y = 0.f;
        float movement_speed = 5.f;
        // Create an instance of the Laser class using the constructor
        Laser laser(position_x, position_y, direction_x, direction_y, movement_speed);
        // Check if the laser object is initialized correctly
        // Test position
        if (laser.getPosition().x != position_x || laser.getPosition().y != position_y) {
            std::cout << "Constructor test failed! Incorrect position." << std::endl;
        }
        // Test direction
        if (laser.getDirection().x != direction_x || laser.getDirection().y != direction_y) {
            std::cout << "Constructor test failed! Incorrect direction." << std::endl;
        }
        // Test movement speed
        if (laser.getMovementSpeed() != movement_speed) {
            std::cout << "Constructor test failed! Incorrect movement speed." << std::endl;
        }
        // If all checks pass, the test is successful
        std::cout << "Constructor test passed!" << std::endl;
    }
    
};

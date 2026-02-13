// this file will run unit tests on the alien class
#include <iostream>
#include "Alien.h"
class AlienTest {
public:
    void runAlienTests() {
        testGetPoints();
    }
private:

//this test ensure that the getpoints function returns the correct point of the alien
   void testGetPoints() {
        // Create an instance of the Alien class
        Alien alien(100.f, 200.f);
        // Set the expected points of the alien
        int expectedPoints = 5;
        // Get the actual points of the alien
        const int& actualPoints = alien.getPoints();
        // Compare the expected and actual points
        if (actualPoints != expectedPoints) {
    std::cout << "getPoints() test failed!" << std::endl;
} else {
    std::cout << "getPoints() test passed!" << std::endl;
}
    }
};

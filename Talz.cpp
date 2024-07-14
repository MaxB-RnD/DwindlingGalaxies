// Defintions of the functions and variables declared in the Talz.h file. 
#include <SFML/Graphics.hpp>
#include <iostream>
#include "Alien.h"
#include "Talz.h"

using namespace sf;
using namespace std;

// CONSTRUCTORS
    // Defualt Constructor
    Talz::Talz(){}

    // Specific Constructor
    Talz::Talz(float pos_x, float pos_y) : Alien() {
        // Set Image of the Body
            setImage("Images/Talz.png");
        // Set Position
            body->setPosition(pos_x, pos_y);
    }


// Movement Function
void Talz::update() {
    body->move(-1.5f, -2.5f);
}


// Deconstructor
Talz::~Talz() {}
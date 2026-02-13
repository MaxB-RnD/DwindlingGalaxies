// Code for all the functions and variables delcared in the Helgahst.h file.
#include "Helghast.h"
#include "Alien.h"

#include <SFML/Graphics.hpp>
#include <iostream>

using namespace sf;
using namespace std;

// CONSTRUCTORS
    // Default Constructors
    Helghast::Helghast(){}

    // Specific Constructor
    Helghast::Helghast(float pos_x, float pos_y) : Alien() {
        // Set Image of the Body
            setImage("Images/Helgahst.png");
        // Set Position
            body->setPosition(pos_x, pos_y);
    }


// Movement Function 
void Helghast::update(){
    body->move(5.f, 1.f);
}


// Deconstructor
Helghast::~Helghast() {}
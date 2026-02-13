// Definition of the functions and variables declared in the Mondoshawn.h file.
#include <SFML/Graphics.hpp>
#include "MondoShawn.h"
#include "Alien.h"

using namespace sf;
using namespace std;

// CONSTRUCTORS
    // Defualt Constructor
    MondoShawn::MondoShawn(){}

    // Specific Constructor
    MondoShawn::MondoShawn(float pos_x, float pos_y) : Alien() {
        // Set Image of the Body
            setImage("Images/MondoShawns.png");
        // Set Position
            body->setPosition(pos_x, pos_y);
    }


// Movement Function
void MondoShawn::update(){
    body->move(1.f, 2.5f);
}


// Deconstructor
MondoShawn::~MondoShawn() {}
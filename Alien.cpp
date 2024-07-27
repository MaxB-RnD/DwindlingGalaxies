// This files defines all of the functions and varbales declared in Alien.h
#include <SFML/Graphics.hpp>
#include "Alien.h"

using namespace sf;
using namespace std;

//  DEFINE THE CREATION OF THE OBJECT
   // Initalise Varibale Values
    void Alien::initVariables(){
        points = 50;
        speed = 2.5f;
    }

    // Initalise Shape Dimension and Bounds
    void Alien::initShape(){
        // Set Scale of the Body 
            body->setScale(0.20f,0.20f);

        // Set Origion of the Body
            FloatRect bodySize = body->getGlobalBounds();    
            body->setOrigin(bodySize.width/2.,bodySize.height/2.);
            
        // Save Values as Width and Height
            width = bodySize.width/2;
            height = bodySize.height/2;
    }

    // Base constructor
    Alien::Alien() {
        initShape();
        initVariables();
    }   


// SPECIFIC CONSTRUCTOR
    Alien::Alien(float pos_x, float pos_y) {
        // Set Image of the Body
            setImage("Libraries/Images/alienShip3.png");
        // Set Position
            body->setPosition(pos_x, pos_y);
        // Scale and Set Origion of Body
            initShape();
        // Intalise Variabel Values
            initVariables();
}


// GAME DYNAMICS & DATA HANDELING
    // Movement Function
    const FloatRect Alien::getBounds() const{
        return body->getGlobalBounds();
    }


//GETTERS & SETTERS
    // Get the number of points the alien is worth
    const int& Alien::getPoints() const{
        return points;
    }


// DECONSTRUCTOR
Alien::~Alien(){

}
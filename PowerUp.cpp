// This file will define variables and functions made in PowerUp.h
#include <SFML/Graphics.hpp>
#include "PowerUp.h"
using namespace sf;
using namespace std;
//  DEFINE THE CREATION OF THE OBJECT
   // Initalise Varibale Values
    void PowerUp::initVariables(){
        points = 25;
        speed = 2.5f;
    }
    // Initalise Shape Dimension and Bounds
    void PowerUp::initShape(){
        // Set Scale of the Body 
            body->setScale(0.35f,0.35f);
        // Set Origin of the Body
            FloatRect bodySize = body->getGlobalBounds();    
            body->setOrigin(bodySize.width/2.,bodySize.height/2.);
            
            // Save Values as Width and Height
                width = bodySize.width/2;
                height = bodySize.height/2;
    }
// SPECIFIC CONSTRUCTOR
    PowerUp::PowerUp() {
        // Scale and Set Origion of Body
            initShape();
        // Intalise Variabel Values
            initVariables();
            }
            
// SPECIFIC CONSTRUCTOR
    PowerUp::PowerUp(float pos_x, float pos_y) {
        // Set Image of the Body
            setImage("Images/PowerUp_01.png");
        // Set Position
            body->setPosition(pos_x, pos_y);
        // Scale and Set Origion of Body
            initShape();
        // Intalise Variabel Values
            initVariables();
            }
//GETTERS & SETTERS
    // Get Bounds of the Body
    const FloatRect PowerUp::getBounds() const{
        return body->getGlobalBounds();
    }
    // Get the number of points the PowerUp is worth
    const int& PowerUp::getPoints() const{
        return points;
    }
    //Change Speed
    void PowerUp::changeSpeed(float new_speed){
        speed = new_speed;
    }
// DECONSTRUCTOR
PowerUp::~PowerUp(){
}

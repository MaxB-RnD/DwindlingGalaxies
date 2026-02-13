// Base Class for the Alien Classes to Inherit from
#ifndef ALIEN_H
#define ALIEN_H

#include <SFML/Graphics.hpp>

using namespace sf;
using namespace std;

#include "GameEntity.h"

class Alien : public GameEntity {

    private:
        // Variables for Movement
            float speed;
            int points;

        //Define the Creation of the Object
            void initVariables();
            void initShape();


    public:
        //Base Constructor
            Alien();

        // Specific Constructor
            Alien(float pos_x, float pos_y);

        // Game Dynamics and Data Handling
            virtual void update() = 0;
    
        //Getters & Setters
            const int& getPoints() const;
            const FloatRect getBounds() const; 
        
        // Deconstructor
            virtual ~Alien();
};

#endif
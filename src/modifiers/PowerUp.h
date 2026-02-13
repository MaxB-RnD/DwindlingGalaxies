// This file will create the PowerUp class
#ifndef POWERUP_H
#define POWERUP_H
#include <SFML/Graphics.hpp>
using namespace sf;
using namespace std;
#include "GameEntity.h"
class PowerUp : public GameEntity {
    protected:
        // Variables for Movement
            float speed;
            int points;
        //Define the Creation of the Object
            void initVariables();
            void initShape();
    public:
        // Specific Constructor
            PowerUp();
            PowerUp(float pos_x, float pos_y);
        // Game Dynamics and Data Handling
        virtual void update() =0;
        // Effect
        virtual int powerUpEffect()=0; 
    
        //Getters & Setters
            const FloatRect getBounds() const;   
            const int& getPoints() const;
            void changeSpeed(float new_speed);
        
        // Deconstructor
            virtual ~PowerUp();
};
#endif

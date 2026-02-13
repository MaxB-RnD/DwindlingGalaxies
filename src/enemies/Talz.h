// The Class defineitons for the Talz enemy, which inherits from Alien
#ifndef TALZ_H
#define TALZ_H

#include <SFML/Graphics.hpp>
#include "Alien.h"

using namespace sf;
using namespace std;

class Talz : public Alien{
    public:
        // Constructors
            Talz();
            Talz(float pos_x, float pos_y);

        // Movement Function
            void update();

        // Deconstructor
            ~Talz();
};

#endif
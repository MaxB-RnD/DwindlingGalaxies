// Definition of the Helgahst enemey, which inherits from the Alien class.
#ifndef HELGHAST_H
#define HELGHAST_H

#include <SFML/Graphics.hpp>
#include "Alien.h"

using namespace sf;
using namespace std;

class Helghast : public Alien{
    public:
        // Constructors
            Helghast(float pos_x, float pos_y);
            Helghast();

        // Movement Function
            void update();

        // Deconstructor
            ~Helghast();

};



#endif // MARTIAN_H
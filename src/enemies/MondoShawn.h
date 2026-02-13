// Defintition of the MondoShawn eneemy class, which inherits from Alien.
#ifndef MONDOSHAWN_H
#define MONDOSHAWN_H

#include <SFML/Graphics.hpp>
#include "Alien.h"

using namespace sf;
using namespace std;

class MondoShawn : public Alien{
    public:
        // Constructors
            MondoShawn();
            MondoShawn(float pos_x, float pos_y);

        // Movement Function
            void update();

        // Deconstructor
            ~MondoShawn();
};



#endif // MARTIAN_H
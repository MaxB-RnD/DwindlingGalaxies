// This file will create the GameEntity class
#ifndef GAMEENTITY_H
#define GAMEENTITY_H

#include <SFML/Graphics.hpp>
#include <string.h>

using namespace sf;
using namespace std;

class GameEntity{
    protected:
        // Body Creation for all inhertited Objects
            Texture shape;
            Sprite* body = new Sprite;

        // Size Perameters
            int width;
            int height;
    public:
        // Image setting and Rendering
            void setImage(const string picture);
            void draw(RenderWindow* win);
        
        // Posititon Functions
            int get_x();
            int get_y();
            int get_width();
            int get_height();
            void set_position(Vector2f position);
        
        // Game Dynamics and Data handeling
            const FloatRect getBounds();
            virtual void update();
            virtual ~GameEntity();
};
#endif

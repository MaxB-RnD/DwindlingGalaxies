// Main Class definition for the game Dwindiling galaxies, all screen dynamics handeled here
#ifndef DWINDLINGGALAXIES_H
#define DWINDLINGGALAXIES_H

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <string.h>

#include "Player.h"
#include "DwindlingGalaxies.h"
#include "GameEntity.h"
#include "Laser.h"
#include "GameMenu.h"
#include "Alien.h"
#include "Lives.h"
#include "PowerUp.h"
#include "FasterFiring.h"
#include "ExtraLive.h"
#include "Talz.h"
#include "Helghast.h"
#include "MondoShawn.h"

using namespace sf;
using namespace std;

class DwindlingGalaxies{
    private:
        // Make Render Window
            RenderWindow* win;
        
        //Background Image & Tiles
            Texture* wallpaper = new Texture;
            Texture* world = new Texture;
            Sprite* background = new Sprite;
            Sprite* background1 = new Sprite;
            Sprite* background2 = new Sprite;
            Sprite* planet = new Sprite;
        
        //Scaling Variables
            //Get size of texture.
                Vector2u TextureSize;
            //Get size of window. 
                Vector2u WindowSize;  
        
        // Make Objects
            Player* player;
            vector<Laser*> lasers;
            vector<Alien*> aliens;
            vector<PowerUp*> powerUps;

        //Alien Elements
            float alienSpawnTimer;
            float spawnTimer;
            float spawnTimerMax;
            bool alienSwitch = true;
    
        //PowerUp Elements
            float powerUpSpawnTimer;
            float spawnTimerPU;
            float spawnTimerMaxPU;
            int shots = 0;
            bool switchOn = true;
            bool helghastOn = true;
            bool liveOn;

        // Game Menu
            GameMenu menu;
            bool restart = false;

        // Screen Scrolling for View
            View* view;
            Vector2f position;
        
        //Sounds and Music
            SoundBuffer blaster;
            Sound laser_sound;
            Music* titleScreen;
            SoundBuffer playerDies;
            Sound teleport;
            SoundBuffer levelSound;
            Sound levelUp;
            SoundBuffer alienDeath;
            Sound explosion;
            SoundBuffer powerUpCollision;
            Sound powerUpSound;
        
        // Tilte Bar Elements
            RectangleShape titleBarBackground;
            Text score_info;
            Font score_font;
            Text level_info;
            Font level_font;
            vector<Lives*> lives;

        // Game Display and Menu Dynamics
            int score = 0;
            int scoreTrack = 0;
            int level = 1;
            int num_lives = 3;
            int difficulty;
            int* addScore = new int;
            string userName;
            int scoreSave = 0;
                
        
    public:
        // Defualt Constructor
            DwindlingGalaxies();
        
        // Image Functions
            void setBackground(const string picture);
            void setImage(const string picture);
            void scaleImage();
        
        // Sound Functions
            void music();

        // Screen Dynamics
            void screenScroll();
            void screenView();
            void titleBar();
            void runMenu();
        
        // Object Controls
            void drawFrame();
            void updateLasers();
            void updateLevel();
            void updateDifficulty();
            void updateHighScore();
            void displayHighScore();
            void showHighScore(int x, int y, string word, RenderWindow* window, Font* font);
        
        //PowerUp Elements
            void initPowerUps();
            void updatePowerUps();
            
        //Alien Elements
            void initAliens();
            void updateAliens();
            void updateCombat();
        
        // Player Controls
            void keyboardControls(Event event);
        
        // Game run and data handeling functions
            void restartGame();
            void run();
            virtual ~DwindlingGalaxies();
};
#endif
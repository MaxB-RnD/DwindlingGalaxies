// This file intialises the files and functions to run and prompt the GameMenu class
#ifndef GAMEMENU_H
#define GAMEMENU_H

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
#include <time.h>

#include "Player.h"

using namespace sf;
using namespace std;

class GameMenu{
    private:
        // Game Variables
            RenderWindow* win;
            Vector2u WindowSize;
            Player* player;
        
        // Player Input
            String playerInput;
            Text playerText;
            Font playerFont;
            Event event;

        // Boolean Operators
            bool title = true;
            bool isQuit = false;
            bool isPause = false;
            bool isMenu = false;
            bool isConfirm = false;
            bool runConfirm = false;
            bool mainMenu = false;
            bool isHighScore = false;
            bool isGameOver = true;
            bool isGameMenu = false;
            bool isOptions = false;
            bool isControls = false; 
            bool isAbout = false;
            bool isEasy = false;
            bool isMedium = false;
            bool isExpert = false;
            bool isError = false;
            
            // Graphics
                // Textures
                    Texture studio_logo;
                    Texture main_title;
                    Texture quit_image;
                    Texture pause_image;
                    Texture confirm_image;
                    Texture simple_menu;
                    Texture options_menu;
                    Texture controls_menu; 
                    Texture about_menu;
                    Texture gameOver_image;
                    Texture gameOverMenu_image;
                    Texture quitButton_image;
                    Texture highScore_image;
                    Texture beginner_image;
                    Texture medium_image;
                    Texture expert_image;
                    Texture error_image;
                // Sprites
                    Sprite logo;
                    Sprite titleScene;
                    Sprite popUp;
                    Sprite pauseDialoge;
                    Sprite confirms;
                    Sprite options;
                    Sprite controls; 
                    Sprite about;
                    Sprite menuSprite;
                    Sprite gameOverDialoge;
                    Sprite gameOverMenuDialoge;
                    Sprite quitButton;
                    Sprite highScore;
                    Sprite beginner;
                    Sprite medium;
                    Sprite expert;
                    Sprite error;
                
        // Fade Effect;
            int startAlpha = 0;
            int endAlpha = 255;
            int targetTime = 8000;
            sf::Clock timer;

        //Main menu screen vriable
            int difficulty = 0;

    public:
        // Specific Constructor
            void set_window(RenderWindow* win);
            void set_size(Vector2u WindowSize);
            void set_player(Player* player);
        
        // Title Sequence
            void titleSequence();
        
        // Main Menu
            void displayScreen(Sprite screen); 
            int mainMenuButtons();
            void loadQuitButton();
            // Load Main Menu Sprites
                Sprite mainMenuSprite();
                Sprite easyMode();
                Sprite mediumMode();
                Sprite expertMode();
                Sprite errorSprite();
                Sprite HighScoreSprite();
                Sprite get_optionsSprite();
                Sprite get_controlsSprite();
                Sprite get_aboutSprite();
        
        // Quit Function
            void quit();
        
        // Pause Menu
            void pause();
            bool confirm();
        
        // Game Over Menu
            string gameOver(int* addScore);
            bool gameOverMenu();

        // Getters and Setters
            bool get_title();
            void set_title(bool a_title);
            bool get_quit();
            void set_quit(bool a_quit);
            bool get_pause();
            void set_pause(bool a_pause);
            bool get_confirm();
            void set_confirm(bool a_confirm);
            bool get_menu();
            void set_menu(bool a_menu);
            bool get_easy();
            void set_easy(bool an_easy);
            bool get_medium();
            void set_medium(bool a_medium);
            bool get_expert();
            void set_expert(bool an_expert);
            bool get_error();
            void set_error(bool an_error);
            bool get_highScore();
            void set_highScore(bool a_highScore);
            bool get_options();
            void set_options(bool an_option);
            bool get_controls();
            void set_controls(bool a_control);
            bool get_about();
            void set_about(bool an_about);
            bool get_gameOver();
            void set_gameOver(bool a_gameOver);
            bool get_gameOverMenu();
            void set_gameOverMenu(bool a_gameOverMenu);
            

        // Deconstructor
        virtual ~GameMenu();
};

#endif
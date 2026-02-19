// ------------------------------------------------------------------------------
// -               V E R S I O N   I D E N T I F I C A T I O N -
// ------------------------------------------------------------------------------
// File:                    %name: GameMenu.h %
// Date Created:            %date_created: Tue Feb 17 19:26:55 2026 %
// CM Version               %version: 3 %
// CM Instance              %instance: 1 %
// Author:                  %created_by: MBusato %
// ------------------------------------------------------------------------------
// -                          D E S C R I P T I O N -
// ------------------------------------------------------------------------------
// This file initialises the files and functions to run and prompt the GameMenu
// class. Handles all menu screens including title sequence, main menu,
// difficulty selection, options, controls, about, pause, quit confirmation,
// game over, and high score display. Manages button hit detection and sprite
// loading for each menu state.
//
// ------------------------------------------------------------------------------
// -                          L I C E N S I N G -
// ------------------------------------------------------------------------------
// Copyright (c) 2024 EastSide Lion Studios. All rights reserved. Use of this
// software is subject to the license terms found in the LICENSE file located in
// the root directory of this repository.
// ------------------------------------------------------------------------------
#ifndef GAMEMENU_H
#define GAMEMENU_H

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
#include <time.h>

#include "Player.h"

using namespace sf;
using namespace std;

class GameMenu
{
  public:
    // --------------------------------------------------------------------------
    // DECONSTRUCTOR
    //
    virtual ~GameMenu();

    // --------------------------------------------------------------------------
    // FUNCTION: set_window
    //
    // DESCRIPTION:
    //  Injects the render window pointer for menu rendering.
    //
    // PARAMETERS:
    //  win - Pointer to the render window.
    //
    // RETURNS:
    //  None.
    //
    void set_window(RenderWindow* win);

    // --------------------------------------------------------------------------
    // FUNCTION: set_size
    //
    // DESCRIPTION:
    //  Sets the window size for menu positioning calculations.
    //
    // PARAMETERS:
    //  WindowSize - Window dimensions.
    //
    // RETURNS:
    //  None.
    //
    void set_size(Vector2u WindowSize);

    // --------------------------------------------------------------------------
    // FUNCTION: set_player
    //
    // DESCRIPTION:
    //  Injects the player pointer for camera-relative menu positioning.
    //
    // PARAMETERS:
    //  player - Pointer to the player object.
    //
    // RETURNS:
    //  None.
    //
    void set_player(Player* player);

    // --------------------------------------------------------------------------
    // FUNCTION: titleSequence
    //
    // DESCRIPTION:
    //  Renders the studio logo and main title with fade-in effect.
    //
    // RETURNS:
    //  None.
    //
    void titleSequence();

    // --------------------------------------------------------------------------
    // FUNCTION: displayScreen
    //
    // DESCRIPTION:
    //  Renders a menu sprite with quit button overlay.
    //
    // PARAMETERS:
    //  screen - Sprite to display.
    //
    // RETURNS:
    //  None.
    //
    void displayScreen(Sprite screen);

    // --------------------------------------------------------------------------
    // FUNCTION: mainMenuButtons
    //
    // DESCRIPTION:
    //  Handles mouse click detection on all menu buttons.
    //
    // RETURNS:
    //  Current difficulty selection (0 if none selected).
    //
    int mainMenuButtons();

    // --------------------------------------------------------------------------
    // FUNCTION: loadQuitButton
    //
    // DESCRIPTION:
    //  Loads and renders the quit button in the top-right corner.
    //
    // RETURNS:
    //  None.
    //
    void loadQuitButton();

    // --------------------------------------------------------------------------
    // FUNCTION: mainMenuSprite
    //
    // DESCRIPTION:
    //  Loads and positions the main menu sprite.
    //
    // RETURNS:
    //  Main menu sprite.
    //
    Sprite mainMenuSprite();

    // --------------------------------------------------------------------------
    // FUNCTION: easyMode
    //
    // DESCRIPTION:
    //  Loads and positions the easy difficulty selection sprite.
    //
    // RETURNS:
    //  Easy mode sprite.
    //
    Sprite easyMode();

    // --------------------------------------------------------------------------
    // FUNCTION: mediumMode
    //
    // DESCRIPTION:
    //  Loads and positions the medium difficulty selection sprite.
    //
    // RETURNS:
    //  Medium mode sprite.
    //
    Sprite mediumMode();

    // --------------------------------------------------------------------------
    // FUNCTION: expertMode
    //
    // DESCRIPTION:
    //  Loads and positions the expert difficulty selection sprite.
    //
    // RETURNS:
    //  Expert mode sprite.
    //
    Sprite expertMode();

    // --------------------------------------------------------------------------
    // FUNCTION: errorSprite
    //
    // DESCRIPTION:
    //  Loads and positions the error message sprite.
    //
    // RETURNS:
    //  Error sprite.
    //
    Sprite errorSprite();

    // --------------------------------------------------------------------------
    // FUNCTION: HighScoreSprite
    //
    // DESCRIPTION:
    //  Loads and positions the high score screen sprite.
    //
    // RETURNS:
    //  High score sprite.
    //
    Sprite HighScoreSprite();

    // --------------------------------------------------------------------------
    // FUNCTION: get_optionsSprite
    //
    // DESCRIPTION:
    //  Loads and positions the options menu sprite.
    //
    // RETURNS:
    //  Options sprite.
    //
    Sprite get_optionsSprite();

    // --------------------------------------------------------------------------
    // FUNCTION: get_controlsSprite
    //
    // DESCRIPTION:
    //  Loads and positions the controls diagram sprite.
    //
    // RETURNS:
    //  Controls sprite.
    //
    Sprite get_controlsSprite();

    // --------------------------------------------------------------------------
    // FUNCTION: get_aboutSprite
    //
    // DESCRIPTION:
    //  Loads and positions the about screen sprite.
    //
    // RETURNS:
    //  About sprite.
    //
    Sprite get_aboutSprite();

    // --------------------------------------------------------------------------
    // FUNCTION: quit
    //
    // DESCRIPTION:
    //  Displays quit confirmation dialog and handles button input.
    //
    // RETURNS:
    //  None.
    //
    void quit();

    // --------------------------------------------------------------------------
    // FUNCTION: pause
    //
    // DESCRIPTION:
    //  Displays pause menu and handles button input.
    //
    // RETURNS:
    //  None.
    //
    void pause();

    // --------------------------------------------------------------------------
    // FUNCTION: confirm
    //
    // DESCRIPTION:
    //  Displays confirmation dialog for restart or return to main menu.
    //
    // RETURNS:
    //  True if confirmed, false otherwise.
    //
    bool confirm();

    // --------------------------------------------------------------------------
    // FUNCTION: gameOver
    //
    // DESCRIPTION:
    //  Displays game over screen with name entry field.
    //
    // PARAMETERS:
    //  addScore - Pointer to flag indicating whether to save the score.
    //
    // RETURNS:
    //  Player name as string.
    //
    string gameOver(int* addScore);

    // --------------------------------------------------------------------------
    // FUNCTION: gameOverMenu
    //
    // DESCRIPTION:
    //  Displays game over menu with restart, main menu, and quit options.
    //
    // RETURNS:
    //  True if restarting, false otherwise.
    //
    bool gameOverMenu();

    // --------------------------------------------------------------------------
    // FUNCTION: get_title
    //
    // DESCRIPTION:
    //  Returns the title screen state flag.
    //
    // RETURNS:
    //  True if title screen is active.
    //
    bool get_title();

    // --------------------------------------------------------------------------
    // FUNCTION: set_title
    //
    // DESCRIPTION:
    //  Sets the title screen state flag.
    //
    // PARAMETERS:
    //  a_title - New title state.
    //
    // RETURNS:
    //  None.
    //
    void set_title(bool a_title);

    // --------------------------------------------------------------------------
    // FUNCTION: get_quit
    //
    // DESCRIPTION:
    //  Returns the quit dialog state flag.
    //
    // RETURNS:
    //  True if quit dialog is active.
    //
    bool get_quit();

    // --------------------------------------------------------------------------
    // FUNCTION: set_quit
    //
    // DESCRIPTION:
    //  Sets the quit dialog state flag.
    //
    // PARAMETERS:
    //  a_quit - New quit state.
    //
    // RETURNS:
    //  None.
    //
    void set_quit(bool a_quit);

    // --------------------------------------------------------------------------
    // FUNCTION: get_pause
    //
    // DESCRIPTION:
    //  Returns the pause menu state flag.
    //
    // RETURNS:
    //  True if pause menu is active.
    //
    bool get_pause();

    // --------------------------------------------------------------------------
    // FUNCTION: set_pause
    //
    // DESCRIPTION:
    //  Sets the pause menu state flag.
    //
    // PARAMETERS:
    //  a_pause - New pause state.
    //
    // RETURNS:
    //  None.
    //
    void set_pause(bool a_pause);

    // --------------------------------------------------------------------------
    // FUNCTION: get_confirm
    //
    // DESCRIPTION:
    //  Returns the confirmation dialog state flag.
    //
    // RETURNS:
    //  True if confirmation dialog is active.
    //
    bool get_confirm();

    // --------------------------------------------------------------------------
    // FUNCTION: set_confirm
    //
    // DESCRIPTION:
    //  Sets the confirmation dialog state flag.
    //
    // PARAMETERS:
    //  a_confirm - New confirm state.
    //
    // RETURNS:
    //  None.
    //
    void set_confirm(bool a_confirm);

    // --------------------------------------------------------------------------
    // FUNCTION: get_menu
    //
    // DESCRIPTION:
    //  Returns the main menu state flag.
    //
    // RETURNS:
    //  True if main menu is active.
    //
    bool get_menu();

    // --------------------------------------------------------------------------
    // FUNCTION: set_menu
    //
    // DESCRIPTION:
    //  Sets the main menu state flag.
    //
    // PARAMETERS:
    //  a_menu - New menu state.
    //
    // RETURNS:
    //  None.
    //
    void set_menu(bool a_menu);

    // --------------------------------------------------------------------------
    // FUNCTION: get_easy
    //
    // DESCRIPTION:
    //  Returns the easy difficulty selection state flag.
    //
    // RETURNS:
    //  True if easy mode is selected.
    //
    bool get_easy();

    // --------------------------------------------------------------------------
    // FUNCTION: set_easy
    //
    // DESCRIPTION:
    //  Sets the easy difficulty selection state flag.
    //
    // PARAMETERS:
    //  an_easy - New easy mode state.
    //
    // RETURNS:
    //  None.
    //
    void set_easy(bool an_easy);

    // --------------------------------------------------------------------------
    // FUNCTION: get_medium
    //
    // DESCRIPTION:
    //  Returns the medium difficulty selection state flag.
    //
    // RETURNS:
    //  True if medium mode is selected.
    //
    bool get_medium();

    // --------------------------------------------------------------------------
    // FUNCTION: set_medium
    //
    // DESCRIPTION:
    //  Sets the medium difficulty selection state flag.
    //
    // PARAMETERS:
    //  a_medium - New medium mode state.
    //
    // RETURNS:
    //  None.
    //
    void set_medium(bool a_medium);

    // --------------------------------------------------------------------------
    // FUNCTION: get_expert
    //
    // DESCRIPTION:
    //  Returns the expert difficulty selection state flag.
    //
    // RETURNS:
    //  True if expert mode is selected.
    //
    bool get_expert();

    // --------------------------------------------------------------------------
    // FUNCTION: set_expert
    //
    // DESCRIPTION:
    //  Sets the expert difficulty selection state flag.
    //
    // PARAMETERS:
    //  an_expert - New expert mode state.
    //
    // RETURNS:
    //  None.
    //
    void set_expert(bool an_expert);

    // --------------------------------------------------------------------------
    // FUNCTION: get_error
    //
    // DESCRIPTION:
    //  Returns the error message state flag.
    //
    // RETURNS:
    //  True if error message is active.
    //
    bool get_error();

    // --------------------------------------------------------------------------
    // FUNCTION: set_error
    //
    // DESCRIPTION:
    //  Sets the error message state flag.
    //
    // PARAMETERS:
    //  an_error - New error state.
    //
    // RETURNS:
    //  None.
    //
    void set_error(bool an_error);

    // --------------------------------------------------------------------------
    // FUNCTION: get_highScore
    //
    // DESCRIPTION:
    //  Returns the high score screen state flag.
    //
    // RETURNS:
    //  True if high score screen is active.
    //
    bool get_highScore();

    // --------------------------------------------------------------------------
    // FUNCTION: set_highScore
    //
    // DESCRIPTION:
    //  Sets the high score screen state flag.
    //
    // PARAMETERS:
    //  a_highScore - New high score state.
    //
    // RETURNS:
    //  None.
    //
    void set_highScore(bool a_highScore);

    // --------------------------------------------------------------------------
    // FUNCTION: get_options
    //
    // DESCRIPTION:
    //  Returns the options menu state flag.
    //
    // RETURNS:
    //  True if options menu is active.
    //
    bool get_options();

    // --------------------------------------------------------------------------
    // FUNCTION: set_options
    //
    // DESCRIPTION:
    //  Sets the options menu state flag.
    //
    // PARAMETERS:
    //  an_option - New options state.
    //
    // RETURNS:
    //  None.
    //
    void set_options(bool an_option);

    // --------------------------------------------------------------------------
    // FUNCTION: get_controls
    //
    // DESCRIPTION:
    //  Returns the controls screen state flag.
    //
    // RETURNS:
    //  True if controls screen is active.
    //
    bool get_controls();

    // --------------------------------------------------------------------------
    // FUNCTION: set_controls
    //
    // DESCRIPTION:
    //  Sets the controls screen state flag.
    //
    // PARAMETERS:
    //  a_control - New controls state.
    //
    // RETURNS:
    //  None.
    //
    void set_controls(bool a_control);

    // --------------------------------------------------------------------------
    // FUNCTION: get_about
    //
    // DESCRIPTION:
    //  Returns the about screen state flag.
    //
    // RETURNS:
    //  True if about screen is active.
    //
    bool get_about();

    // --------------------------------------------------------------------------
    // FUNCTION: set_about
    //
    // DESCRIPTION:
    //  Sets the about screen state flag.
    //
    // PARAMETERS:
    //  an_about - New about state.
    //
    // RETURNS:
    //  None.
    //
    void set_about(bool an_about);

    // --------------------------------------------------------------------------
    // FUNCTION: get_gameOver
    //
    // DESCRIPTION:
    //  Returns the game over screen state flag.
    //
    // RETURNS:
    //  True if game over screen is active.
    //
    bool get_gameOver();

    // --------------------------------------------------------------------------
    // FUNCTION: set_gameOver
    //
    // DESCRIPTION:
    //  Sets the game over screen state flag.
    //
    // PARAMETERS:
    //  a_gameOver - New game over state.
    //
    // RETURNS:
    //  None.
    //
    void set_gameOver(bool a_gameOver);

    // --------------------------------------------------------------------------
    // FUNCTION: get_gameOverMenu
    //
    // DESCRIPTION:
    //  Returns the game over menu state flag.
    //
    // RETURNS:
    //  True if game over menu is active.
    //
    bool get_gameOverMenu();

    // --------------------------------------------------------------------------
    // FUNCTION: set_gameOverMenu
    //
    // DESCRIPTION:
    //  Sets the game over menu state flag.
    //
    // PARAMETERS:
    //  a_gameOverMenu - New game over menu state.
    //
    // RETURNS:
    //  None.
    //
    void set_gameOverMenu(bool a_gameOverMenu);

    // --------------------------------------------------------------------------
    // FUNCTION: setClickSound
    //
    // DESCRIPTION:
    //  Sets the sound to be made when the mouse is clicked on a button in the 
    //  game menus. 
    //
    // PARAMETERS:
    //  sound - New sound for when mouse is clicked.
    //
    // RETURNS:
    //  None.
    //
    void setClickSound(sf::Sound* sound);

  private:
    // --------------------------------------------------------------------------
    // Game Variables.
    //
    RenderWindow* win;
    Vector2u WindowSize;
    Player* player;

    // --------------------------------------------------------------------------
    // Player Input.
    //
    String playerInput;
    Text playerText;
    Font playerFont;
    Event event;

    // --------------------------------------------------------------------------
    // Boolean Operators.
    //
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
    bool mouseWasPressed = false;

    // --------------------------------------------------------------------------
    // Graphics - Textures.
    //
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

    // --------------------------------------------------------------------------
    // Graphics - Sprites.
    //
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

    // --------------------------------------------------------------------------
    // Fade Effect.
    //
    int startAlpha = 0;
    int endAlpha = 255;
    int targetTime = 8000;
    sf::Clock timer;

    // --------------------------------------------------------------------------
    // Main Menu Screen Variable.
    //
    int difficulty = 0;

    // --------------------------------------------------------------------------
    // Audio Sounds.
    //
    Sound* clickSound = nullptr;
};

#endif

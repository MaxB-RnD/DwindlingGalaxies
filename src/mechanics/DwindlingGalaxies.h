// ------------------------------------------------------------------------------
// -               V E R S I O N   I D E N T I F I C A T I O N -
// ------------------------------------------------------------------------------
// File:                    %name: DwindlingGalaxies.h %
// Date Created:            %date_created: Tue Feb 17 19:26:55 2026 %
// CM Version               %version: 3 %
// CM Instance              %instance: 1 %
// Author:                  %created_by: MBusato %
// ------------------------------------------------------------------------------
// -                          D E S C R I P T I O N -
// ------------------------------------------------------------------------------
// Main class definition for Dwindling Galaxies. Manages the game window,
// background rendering, screen scrolling, audio, HUD, entity spawning and
// updates, collision detection, scoring, high score file I/O, menu
// orchestration, and the main game loop.
//
// ------------------------------------------------------------------------------
// -                          L I C E N S I N G -
// ------------------------------------------------------------------------------
// Copyright (c) 2024 EastSide Lion Studios. All rights reserved. Use of this
// software is subject to the license terms found in the LICENSE file located in
// the root directory of this repository.
// ------------------------------------------------------------------------------
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

class DwindlingGalaxies
{
  public:
    // --------------------------------------------------------------------------
    // CONSTRUCTOR
    //
    DwindlingGalaxies();

    // --------------------------------------------------------------------------
    // DECONSTRUCTOR
    //
    virtual ~DwindlingGalaxies();

    // --------------------------------------------------------------------------
    // FUNCTION: setBackground
    //
    // DESCRIPTION:
    //  Loads and applies a texture to all background tile sprites.
    //
    // PARAMETERS:
    //  picture - Filepath to the background image.
    //
    // RETURNS:
    //  None.
    //
    void setBackground(const string picture);

    // --------------------------------------------------------------------------
    // FUNCTION: setImage
    //
    // DESCRIPTION:
    //  Loads and applies a texture to the planet sprite.
    //
    // PARAMETERS:
    //  picture - Filepath to the planet image.
    //
    // RETURNS:
    //  None.
    //
    void setImage(const string picture);

    // --------------------------------------------------------------------------
    // FUNCTION: scaleImage
    //
    // DESCRIPTION:
    //  Scales all background images to fit the window size.
    //
    // RETURNS:
    //  None.
    //
    void scaleImage();

    // --------------------------------------------------------------------------
    // FUNCTION: music
    //
    // DESCRIPTION:
    //  Loads all sound effects and background music from disk.
    //
    // RETURNS:
    //  None.
    //
    void music();

    // --------------------------------------------------------------------------
    // FUNCTION: updateMusic
    //
    // DESCRIPTION:
    //  Play/Pauses music in the game menus.
    //
    // RETURNS:
    //  None.
    //
    void updateMusic();

    // --------------------------------------------------------------------------
    // FUNCTION: screenScroll
    //
    // DESCRIPTION:
    //  Initialises the camera view for scrolling.
    //
    // RETURNS:
    //  None.
    //
    void screenScroll();

    // --------------------------------------------------------------------------
    // FUNCTION: screenView
    //
    // DESCRIPTION:
    //  Updates camera position to follow the player with boundary clamping.
    //
    // RETURNS:
    //  None.
    //
    void screenView();

    // --------------------------------------------------------------------------
    // FUNCTION: titleBar
    //
    // DESCRIPTION:
    //  Creates and positions the HUD bar showing score, level, and lives.
    //
    // RETURNS:
    //  None.
    //
    void titleBar();

    // --------------------------------------------------------------------------
    // FUNCTION: runMenu
    //
    // DESCRIPTION:
    //  Orchestrates which screen to display based on current menu state.
    //
    // RETURNS:
    //  None.
    //
    void runMenu();

    // --------------------------------------------------------------------------
    // FUNCTION: drawFrame
    //
    // DESCRIPTION:
    //  Renders all game objects to the window.
    //
    // RETURNS:
    //  None.
    //
    void drawFrame();

    // --------------------------------------------------------------------------
    // FUNCTION: updateLasers
    //
    // DESCRIPTION:
    //  Updates laser positions and removes lasers that exit the camera view.
    //
    // RETURNS:
    //  None.
    //
    void updateLasers();

    // --------------------------------------------------------------------------
    // FUNCTION: updateLevel
    //
    // DESCRIPTION:
    //  Increases level based on score and adjusts alien spawn rate.
    //
    // RETURNS:
    //  None.
    //
    void updateLevel();

    // --------------------------------------------------------------------------
    // FUNCTION: updateDifficulty
    //
    // DESCRIPTION:
    //  Applies difficulty-specific spawn rates for aliens and power-ups.
    //
    // RETURNS:
    //  None.
    //
    void updateDifficulty();

    // --------------------------------------------------------------------------
    // FUNCTION: updateHighScore
    //
    // DESCRIPTION:
    //  Saves a new high score to file and sorts the leaderboard.
    //
    // RETURNS:
    //  None.
    //
    void updateHighScore();

    // --------------------------------------------------------------------------
    // FUNCTION: displayHighScore
    //
    // DESCRIPTION:
    //  Reads and renders the high score leaderboard to the screen.
    //
    // RETURNS:
    //  None.
    //
    void displayHighScore();

    // --------------------------------------------------------------------------
    // FUNCTION: showHighScore
    //
    // DESCRIPTION:
    //  Renders a single high score entry at the specified position.
    //
    // PARAMETERS:
    //  x      - X coordinate.
    //  y      - Y coordinate.
    //  word   - Text to display.
    //  window - Render window pointer.
    //  font   - Font pointer.
    //
    // RETURNS:
    //  None.
    //
    void showHighScore(int x, int y, string word, RenderWindow* window, Font* font);

    // --------------------------------------------------------------------------
    // FUNCTION: initPowerUps
    //
    // DESCRIPTION:
    //  Initialises power-up spawn timers.
    //
    // RETURNS:
    //  None.
    //
    void initPowerUps();

    // --------------------------------------------------------------------------
    // FUNCTION: updatePowerUps
    //
    // DESCRIPTION:
    //  Spawns power-ups, updates their positions, and handles player collision.
    //
    // RETURNS:
    //  None.
    //
    void updatePowerUps();

    // --------------------------------------------------------------------------
    // FUNCTION: initAliens
    //
    // DESCRIPTION:
    //  Initialises alien spawn timers.
    //
    // RETURNS:
    //  None.
    //
    void initAliens();

    // --------------------------------------------------------------------------
    // FUNCTION: updateAliens
    //
    // DESCRIPTION:
    //  Spawns aliens, updates their positions, and handles player collision.
    //
    // RETURNS:
    //  None.
    //
    void updateAliens();

    // --------------------------------------------------------------------------
    // FUNCTION: updateCombat
    //
    // DESCRIPTION:
    //  Detects laser-alien collisions and awards points.
    //
    // RETURNS:
    //  None.
    //
    void updateCombat();

    // --------------------------------------------------------------------------
    // FUNCTION: keyboardControls
    //
    // DESCRIPTION:
    //  Handles player movement and firing input.
    //
    // PARAMETERS:
    //  None.
    //
    // RETURNS:
    //  None.
    //
    void keyboardControls();

    // --------------------------------------------------------------------------
    // FUNCTION: restartGame
    //
    // DESCRIPTION:
    //  Resets game state and clears all entities for a new game.
    //
    // RETURNS:
    //  None.
    //
    void restartGame();

    // --------------------------------------------------------------------------
    // FUNCTION: run
    //
    // DESCRIPTION:
    //  Main game loop. Polls events, updates state, and renders frames.
    //
    // RETURNS:
    //  None.
    //
    void run();

  private:
    // --------------------------------------------------------------------------
    // Render Window.
    //
    RenderWindow* win;

    // --------------------------------------------------------------------------
    // Background Image and Tiles.
    //
    Texture* wallpaper = new Texture;
    Texture* world = new Texture;
    Sprite* background = new Sprite;
    Sprite* background1 = new Sprite;
    Sprite* background2 = new Sprite;
    Sprite* planet = new Sprite;

    // --------------------------------------------------------------------------
    // Scaling Variables.
    //
    Vector2u TextureSize;
    Vector2u WindowSize;

    // --------------------------------------------------------------------------
    // Game Objects.
    //
    Player* player;
    vector<Laser*> lasers;
    vector<Alien*> aliens;
    vector<PowerUp*> powerUps;

    // --------------------------------------------------------------------------
    // Alien Elements.
    //
    float alienSpawnTimer;
    float spawnTimer;
    float spawnTimerMax;
    bool alienSwitch = true;

    // --------------------------------------------------------------------------
    // PowerUp Elements.
    //
    float powerUpSpawnTimer;
    float spawnTimerPU;
    float spawnTimerMaxPU;
    int shots = 0;
    bool switchOn = true;
    bool helghastOn = true;
    bool liveOn;

    // --------------------------------------------------------------------------
    // Game Menu.
    //
    GameMenu menu;
    bool restart = false;

    // --------------------------------------------------------------------------
    // Screen Scrolling for View.
    //
    View* view;
    Vector2f position;

    // --------------------------------------------------------------------------
    // Sounds and Music.
    //
    SoundBuffer blaster;
    Sound laser_sound;
    Music* logoIntro;
    bool logoIntroFinished;
    Music* titleScreen;
    SoundBuffer playerDies;
    Sound teleport;
    SoundBuffer levelSound;
    Sound levelUp;
    SoundBuffer alienDeath;
    Sound explosion;
    SoundBuffer powerUpCollision;
    Sound powerUpSound;
    SoundBuffer clickBuffer;
    Sound       clickSound;
    
    // --------------------------------------------------------------------------
    // Title Bar Elements.
    //
    RectangleShape titleBarBackground;
    Text score_info;
    Font score_font;
    Text level_info;
    Font level_font;
    Font highScore_font;
    bool fontsLoaded = false;
    vector<Lives*> lives;

    // --------------------------------------------------------------------------
    // Game Display and Menu Dynamics.
    //
    int score = 0;
    int scoreTrack = 0;
    int level = 1;
    int num_lives = 3;
    int difficulty;
    int* addScore = new int;
    string userName;
    int scoreSave = 0;
};

#endif

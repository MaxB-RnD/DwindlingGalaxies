// ------------------------------------------------------------------------------
// -               V E R S I O N   I D E N T I F I C A T I O N -
// ------------------------------------------------------------------------------
// File:                    %name: DwindlingGalaxies.cpp %
// Date Created:            %date_created: Tue Feb 17 19:26:55 2026 %
// CM Version               %version: 3 %
// CM Instance              %instance: 1 %
// Author:                  %created_by: MBusato %
// ------------------------------------------------------------------------------
// -                          D E S C R I P T I O N -
// ------------------------------------------------------------------------------
// Core game class for Dwindling Galaxies. It manages the main game loop, window 
// creation, background rendering, audio loading, screen scrolling, HUD, entity 
// spawning and updates, combat resolution, player input, scoring, high scores,
// and menu orchestration.
//
// ------------------------------------------------------------------------------
// -                          L I C E N S I N G -
// ------------------------------------------------------------------------------
// Copyright (c) 2024 EastSide Lion Studios. All rights reserved. Use of this
// software is subject to the license terms found in the LICENSE file located in
// the root directory of this repository.
// ------------------------------------------------------------------------------

#include <algorithm>
#include <cstring>
#include <iostream>
#include <stdio.h>
#include <string.h>
#include <utility>
#include <vector>

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>

#include "Alien.h"
#include "Helghast.h"
#include "MondoShawn.h"
#include "Talz.h"

#include "ExtraLive.h"
#include "FasterFiring.h"
#include "PowerUp.h"

#include "DwindlingGalaxies.h"
#include "GameMenu.h"

#include "GameEntity.h"
#include "Laser.h"
#include "Lives.h"
#include "Player.h"

using namespace sf;
using namespace std;

// ------------------------------------------------------------------------------
// -                         C O N S T R U C T O R -
// ------------------------------------------------------------------------------
DwindlingGalaxies::DwindlingGalaxies()
{
  // Platform-specific Window Creation.
  #ifdef _WIN32
    // Windows Platform.
    win = new RenderWindow(VideoMode(1920, 1080), "Dwindling Galaxies");
  #elif __linux__
    // Linux Platform.
    VideoMode desktop = VideoMode::getDesktopMode();
    win = new RenderWindow(desktop, "Dwindling Galaxies", Style::Fullscreen);
  #else
    // Fall-Back for all Platforms.
    win = new RenderWindow(VideoMode(1280, 720), "Dwindling Galaxies");
  #endif

  // Set Window Icon.
  sf::Image icon;
  if (icon.loadFromFile("Images/Logo.png")) 
  {
    win->setIcon(icon.getSize().x, icon.getSize().y, icon.getPixelsPtr());
  }

  // Load and Scale Background Images.
  setBackground("Images/background3.png");
  setImage("Images/Planet3.png");
  TextureSize = wallpaper->getSize();
  WindowSize  = win->getSize();
  scaleImage();

  // Position bBackground Tiles and Planet.
  background1->setPosition(Vector2f(WindowSize.x * 2, WindowSize.y));
  background2->setPosition(Vector2f(0, WindowSize.y));
  planet->setPosition(Vector2f(WindowSize.x * -0.15, WindowSize.y * 0.5));

  // Create Game Objects.
  player = new Player("Images/SpaceShip5.png", WindowSize.x / 2, WindowSize.y / 2);
  initPowerUps();
  initAliens();

  // Set-Up Menu.
  menu.set_player(player);
  menu.set_size(WindowSize);
  menu.set_window(win);

  // Set-Up Scrolling Camera.
  screenScroll();

  // Reserve Vector Capacity to Avoid Reallocation Mid-Game.
  lasers.reserve(100);
  aliens.reserve(50);
  powerUps.reserve(20);

  // Window Performance Settings.
  win->setVerticalSyncEnabled(true);
  win->setFramerateLimit(60);
}
// ------------------------------------------------------------------------------


// ------------------------------------------------------------------------------
// -                        D E S T R U C T O R -
// ------------------------------------------------------------------------------
DwindlingGalaxies::~DwindlingGalaxies()
{
  // Stop ALL Audio First.
  if(logoIntro)
  {
    logoIntro->stop();
    delete logoIntro;
    logoIntro = nullptr;
  }
  if(titleScreen) 
  {
    titleScreen->stop();
    delete titleScreen;
    titleScreen = nullptr;
  }
  
  // Stop All Sound Effects
  laser_sound.stop();
  teleport.stop();
  levelUp.stop();
  explosion.stop();
  powerUpSound.stop();
  clickSound.stop();
  
  // Reset Buffers (Releases OpenAL Resources).
  laser_sound.resetBuffer();
  teleport.resetBuffer();
  levelUp.resetBuffer();
  explosion.resetBuffer();
  powerUpSound.resetBuffer();
  clickSound.resetBuffer();

  // Release Variables from Memory.
  delete addScore;
  delete background;
  delete background1;
  delete background2;
  delete planet;
  delete wallpaper;
  delete world;

  delete win;
  delete view;
  delete player;

  for(auto *i : lasers)   delete i;
  for(auto *i : lives)    delete i;
  for(auto *i : powerUps) delete i;
  for(auto *i : aliens)   delete i;
}
// ------------------------------------------------------------------------------


// ------------------------------------------------------------------------------
// -                      I M A G E   F U N C T I O N S -
// ------------------------------------------------------------------------------
void DwindlingGalaxies::setBackground(const string picture)
{
  // Attempt to Load Texture.
  if(!wallpaper->loadFromFile(picture))
  {
    // Terminate if Asset is Missing.
    cout << "Background Image Not Found" << endl;
    exit(0);
  }

  // Assign the Same Loaded Texture to all Background Layers.
  background->setTexture(*wallpaper);
  background1->setTexture(*wallpaper);
  background2->setTexture(*wallpaper);
}

void DwindlingGalaxies::setImage(const string picture)
{
  // Attempt to Load Texture.
  if(!world->loadFromFile(picture))
  {
    // Terminate if Asset is Missing.
    cout << "Planet Image Not Found" << endl;
    exit(0);
  }
  
  // Assign the Same Loaded Texture to the Planet Layer.
  planet->setTexture(*world);
}

void DwindlingGalaxies::scaleImage()
{
  // Calculate Ratios Between Window Dimensions & Native Texture Size.
  float ScaleX = (float)WindowSize.x / TextureSize.x;
  float ScaleY = (float)WindowSize.y / TextureSize.y;

  // Apply Scale to the Main Background.
  background->setScale(ScaleX,   ScaleY);

  // Apply Inverted Scales to Auxiliary Backgrounds.
  background1->setScale(-ScaleX, -ScaleY);
  background2->setScale(-ScaleX, -ScaleY);

  // Ensure the Planet Sprite Matches the World Scaling.
  planet->setScale(ScaleX, ScaleY);
}
// ------------------------------------------------------------------------------


// ------------------------------------------------------------------------------
// -                      A U D I O   F U N C T I O N S -
// ------------------------------------------------------------------------------
void DwindlingGalaxies::music()
{
  // Producer Logo Screen Music.
  logoIntro = new Music;
  if(!logoIntro->openFromFile("Sounds/logoSequence.wav"))
  {
    cout << "Logo Intro Sound File Not Found" << endl;
    exit(0);
  }
  logoIntroFinished = false;
  logoIntro->setLoop(false);
  logoIntro->play();

  // Title Screen Music.
  titleScreen = new Music;
  if(!titleScreen->openFromFile("Sounds/titleSequence.wav"))
  {
    cout << "Title Sound File Not Found" << endl;
    exit(0);
  }
  titleScreen->setLoop(true); 

  // Laser Firing Sound.
  if(!blaster.loadFromFile("Sounds/blaster.wav"))
  {
    cout << "Laser Sound File Not Found" << endl;
    exit(0);
  }
  laser_sound.setBuffer(blaster);
  laser_sound.setVolume(30);

  // Player Death / Teleport Sound.
  if(!playerDies.loadFromFile("Sounds/teleport.wav"))
  {
    cout << "Teleport Sound File Not Found" << endl;
    exit(0);
  }
  teleport.setBuffer(playerDies);
  teleport.setVolume(50);

  // Level-Up Sound.
  if(!levelSound.loadFromFile("Sounds/levelUp.wav"))
  {
    cout << "Level Up Sound File Not Found" << endl;
    exit(0);
  }
  levelUp.setBuffer(levelSound);

  // Alien Explosion Sound.
  if(!alienDeath.loadFromFile("Sounds/explosion.wav"))
  {
    cout << "Explosion Sound File Not Found" << endl;
    exit(0);
  }
  explosion.setBuffer(alienDeath);

  // Power-Up Collected Sound.
  if(!powerUpCollision.loadFromFile("Sounds/powerUp.wav"))
  {
    cout << "PowerUp Sound File Not Found" << endl;
    exit(0);
  }
  powerUpSound.setBuffer(powerUpCollision);
  powerUpSound.setVolume(85);

  // Button Click Sound.
  if(!clickBuffer.loadFromFile("Sounds/click.wav"))
  {
    cout << "Click Sound File Not Found" << endl;
    exit(0);
  }
  clickSound.setBuffer(clickBuffer);
}

void DwindlingGalaxies::updateMusic(){ 
  // Use Same Menu Check as Keyboard Controls.
  bool inMenu = menu.get_title()     || menu.get_menu()    || menu.get_error()    ||
                menu.get_highScore() || menu.get_options() || menu.get_controls() || 
                menu.get_about()     || menu.get_quit()    || menu.get_pause()    || 
                menu.get_confirm()   || menu.get_gameOverMenu() || menu.get_easy()|| 
                menu.get_medium()    || menu.get_expert() || (menu.get_gameOver() && num_lives == 0);
  
  // Check if Producer Stuido Logo is Done Playing.
  if(!logoIntroFinished && logoIntro->getStatus() == Music::Stopped)  
  {
    logoIntroFinished = true;
    titleScreen->play();
  }

  // Run Normal Title Screen Music.
  if(logoIntroFinished)
  {
    if(!inMenu) 
    { 
      // Pause Music During Gameplay. 
      if(titleScreen->getStatus() == Music::Playing)
      {
        titleScreen->pause(); 
      }
    } 
    else 
    { 
      // Play Music in Menus. 
      if(titleScreen->getStatus() != Music::Playing)
      {
        titleScreen->play();
      } 
    } 
  }
}
// ------------------------------------------------------------------------------


// ------------------------------------------------------------------------------
// -                     S C R E E N   D Y N A M I C S -
// ------------------------------------------------------------------------------
void DwindlingGalaxies::screenScroll()
{
  view = new View;
  view->reset(FloatRect(0, 0, WindowSize.x, WindowSize.y));
  view->setViewport(FloatRect(0, 0, 1.0f, 1.0f));
  position = Vector2f(WindowSize.x / 2, WindowSize.y / 2);
}

void DwindlingGalaxies::screenView()
{
  // Clamp Camera so it Doesn't Scroll Past the Playable Area Edges.
  if(player->get_x() > WindowSize.x * 1.5)
  {
    position.x = WindowSize.x * 1.5;
  }
  else if(player->get_x() < WindowSize.x * -0.5)
  {
    position.x = WindowSize.x * -0.5;
  }
  else
  {
    position.x = player->get_x();
  }

  // Set Camera & Screen View. 
  view->setCenter(position);
  win->setView(*view);
}

void DwindlingGalaxies::titleBar()
{
  // Set Background Bar Shape.
  titleBarBackground.setSize(Vector2f(WindowSize.x, 75));
  titleBarBackground.setFillColor(Color::Black);
  titleBarBackground.setOrigin(WindowSize.x / 2, 75 / 2);
  titleBarBackground.setOutlineColor(Color(102, 0, 102));
  titleBarBackground.setOutlineThickness(5);

  // Display Score Text.
  if(!score_font.loadFromFile("Fonts/Future_Now.ttf"))
  {
    cout << "Score Font Not Found" << endl;
    exit(0);
  }
  score_info.setFont(score_font);
  score_info.setFillColor(Color::White);
  score_info.setCharacterSize(50);
  score_info.setString("SCORE: " + to_string(score) + " ");

  // Display Level Text.
  if(!level_font.loadFromFile("Fonts/Future_Now.ttf"))
  {
    cout << "Level Font Not Found" << endl;
    exit(0);
  }
  level_info.setFont(level_font);
  level_info.setFillColor(Color::White);
  level_info.setCharacterSize(50);
  level_info.setString("Level " + to_string(level) + " ");
  FloatRect bodySize = level_info.getGlobalBounds();
  level_info.setOrigin(bodySize.width / 2., bodySize.height / 2.);

  // Display Lives Icons.
  for(int i = 0; i < 5; i++)
  {
    lives.push_back(new Lives(0.95 * WindowSize.x, 30, 130 * i));
  }

  // Track the HUD Bar to the Camera Position.
  int distance = (WindowSize.x / 2) - 20;
  if(player->get_x() > WindowSize.x * 1.5)
  {
    titleBarBackground.setPosition(1.5 * WindowSize.x, 75 / 2);
    score_info.setPosition((WindowSize.x) + 20, 5);
    level_info.setPosition(1.5 * WindowSize.x, 20);
  }
  else if(player->get_x() < WindowSize.x * -0.5)
  {
    titleBarBackground.setPosition(-0.5 * WindowSize.x, 75 / 2);
    score_info.setPosition((-0.5 * WindowSize.x) - 940, 5);
    level_info.setPosition(-0.5 * WindowSize.x, 20);
  }
  else
  {
    titleBarBackground.setPosition(player->get_x(), 75 / 2);
    score_info.setPosition(player->get_x() - distance, 5);
    level_info.setPosition(player->get_x(), 20);
  }
}
// ------------------------------------------------------------------------------


// ------------------------------------------------------------------------------
// -                          M E N U   L O G I C -
// ------------------------------------------------------------------------------
void DwindlingGalaxies::runMenu()
{
  if(menu.get_title() == true)
  {
    screenView();
    menu.titleSequence();
  }
  else if(menu.get_menu() == true)
  {
    screenView();
    menu.displayScreen(menu.mainMenuSprite());
    difficulty = menu.mainMenuButtons();
  }
  else if(menu.get_easy() == true)
  {
    screenView();
    menu.displayScreen(menu.easyMode());
    difficulty = menu.mainMenuButtons();
  }
  else if(menu.get_medium() == true)
  {
    screenView();
    menu.displayScreen(menu.mediumMode());
    difficulty = menu.mainMenuButtons();
  }
  else if(menu.get_expert() == true)
  {
    screenView();
    menu.displayScreen(menu.expertMode());
    difficulty = menu.mainMenuButtons();
  }
  else if(menu.get_error() == true)
  {
    static Clock displayTimer;
    int displayTimerMax = 2000;
    int currentTime = displayTimer.getElapsedTime().asMilliseconds();
    if(currentTime <= displayTimerMax)
    {
      menu.displayScreen(menu.errorSprite());
    }
    else
    {
      displayTimer.restart();
      menu.set_error(false);
      menu.set_menu(true);
    }
  }
  else if(menu.get_highScore() == true)
  {
    screenView();
    menu.displayScreen(menu.HighScoreSprite());
    difficulty = menu.mainMenuButtons();
    displayHighScore();
  }
  else if(menu.get_options() == true)
  {
    screenView();
    menu.displayScreen(menu.get_optionsSprite());
    difficulty = menu.mainMenuButtons();
  }
  else if(menu.get_controls() == true)
  {
    screenView();
    menu.displayScreen(menu.get_controlsSprite());
    difficulty = menu.mainMenuButtons();
  }
  else if(menu.get_about() == true)
  {
    screenView();
    menu.displayScreen(menu.get_aboutSprite());
    difficulty = menu.mainMenuButtons();
  }
  else if(menu.get_quit() == true)
  {
    screenView();
    menu.quit();
  }
  else if(menu.get_pause() == true)
  {
    screenView();
    menu.pause();
  }
  else if(menu.get_confirm() == true)
  {
    screenView();
    restart = menu.confirm();
  }
  else if(menu.get_gameOver() == true && num_lives == 0)
  {
    screenView();
    scoreSave = score;
    userName = menu.gameOver(addScore);
  }
  else if(menu.get_gameOverMenu() == true)
  {
    screenView();
    restart = menu.gameOverMenu();
    updateHighScore();
  }
  else
  {
    // Active Gameplay
    screenView();
    updateLasers();
    updateLevel();
    updateAliens();
    updateCombat();
    updatePowerUps();
    titleBar();
    drawFrame();
  }
}
// ------------------------------------------------------------------------------


// ------------------------------------------------------------------------------
// -                      O B J E C T   C O N T R O L S -
// ------------------------------------------------------------------------------
void DwindlingGalaxies::drawFrame()
{
  // Set Background Layers.
  background1->setScale(-1.f, -1.f);
  win->draw(*background);
  win->draw(*background1);
  win->draw(*background2);
  win->draw(*planet);

  // Game Entities.
  for(auto *laser : lasers)   laser->draw(win);
  for(auto *alien : aliens)   alien->draw(win);
  for(auto *pu    : powerUps) pu->draw(win);
  player->draw(win);

  // Draw HUD.
  win->draw(titleBarBackground);
  win->draw(score_info);
  win->draw(level_info);
  for(int i = 0; i < num_lives; i++)
  {
    lives[i]->update(player, WindowSize);
    lives[i]->draw(win);
  }
}

void DwindlingGalaxies::updateLasers()
{
  // Calculate Visible Camera Bounds.
  Vector2f viewCenter  = view->getCenter();
  float viewLeft       = viewCenter.x - WindowSize.x / 2.0f;
  float viewRight      = viewCenter.x + WindowSize.x / 2.0f;
  float viewTop        = viewCenter.y - WindowSize.y / 2.0f;
  float viewBottom     = viewCenter.y + WindowSize.y / 2.0f;
  const float MARGIN   = 150.0f;

  // Iterate Backwards for Safe in-loop Deletion.
  for(int i = lasers.size() - 1; i >= 0; i--)
  {
    lasers[i]->update();
    float lx = lasers[i]->get_x();
    float ly = lasers[i]->get_y();

    // Cull Laser if it Exits the Camera Bounds Plus Margin.
    if(lx < viewLeft  - MARGIN || lx > viewRight  + MARGIN ||
      ly < viewTop   - MARGIN || ly > viewBottom + MARGIN)
    {
      delete lasers[i];
      lasers.erase(lasers.begin() + i);
    }
  }
}

void DwindlingGalaxies::updateLevel()
{
  // Level-Up Every 350 Points.
  if(score - scoreTrack == 350)
  {
    levelUp.play();
    level++;
    if(level > 5) level = 5;
    scoreTrack = score;
  }

  // Scale Spawn Intensity Based on Current Level.
  switch(level)
  {
    case 1: case 2: case 3: case 4:
      alienSpawnTimer += 0.25;
      break;
    case 5:
      alienSpawnTimer += 0.5;
      break;
    default:
      break;
  }
}

void DwindlingGalaxies::updateDifficulty()
{
  switch(difficulty)
  {
    case 1: // Easy
      alienSpawnTimer   = 1.25;
      powerUpSpawnTimer = 0.2;
      break;
    case 2: // Medium
      alienSpawnTimer   = 1.75;
      powerUpSpawnTimer = 0.1;
      break;
    case 3: // High
      alienSpawnTimer   = 2.00;
      powerUpSpawnTimer = 0.05;
      break;
    default:
      break;
  }
}
// ------------------------------------------------------------------------------


// ------------------------------------------------------------------------------
// -                      H I G H   S C O R E   I / O -
// ------------------------------------------------------------------------------
void DwindlingGalaxies::updateHighScore()
{
  Font highScoreText;
  vector<pair<int, string>> userScore;
  FILE* highScoreData;
  int   highScore[11];
  char  temp[255];
  string name[11];
  
  // Ensure Assets are Present Before Processing.
  if(!highScoreText.loadFromFile("Fonts/Future_Now.ttf"))
  {
    cout << "High Score Font Not Found" << endl;
    exit(0);
  }

  // Read Existing Scores from the Text File.
  highScoreData = fopen("Scores/highScores.txt", "r");
  for(int i = 0; i < 11; i++)
  {
    fscanf(highScoreData, "%s", temp);
    name[i] = temp;
    fscanf(highScoreData, "%d", &highScore[i]);
    userScore.push_back(make_pair(highScore[i], name[i]));
  }
  fclose(highScoreData);

  // Add New Score if Flag is Set (Triggered on Game Over/Win).
  if(*addScore == 1)
  {
    // Remove Placeholder Null Entries.
    userScore.erase(remove_if(userScore.begin(), userScore.end(), [](const pair<int, string>& p){return p.second == "null" || p.first == 0;}), userScore.end());

    // Insert New Score & Sort Highest First.
    userScore.push_back(make_pair(scoreSave, userName));
    stable_sort(userScore.begin(), userScore.end(), [](const pair<int, string>& a, const pair<int, string>& b){return a.first > b.first;});

    // Keep Only Top 10, Pad Remainder with Nulls for File Format.
    if(userScore.size() > 10) userScore.resize(10);
    while(userScore.size() < 11) userScore.push_back(make_pair(0, "null"));

    // Reset Flag to Prevent Duplicate Entries.
    *addScore = 0;
  }
  else
  {
    // Standard Sort if No New Score is Added.
    stable_sort(userScore.begin(), userScore.end(), [](const pair<int, string>& a, const pair<int, string>& b){return a.first > b.first;}); 
  }

  // Write Sorted Scores Back to File.
  highScoreData = fopen("Scores/highScores.txt", "w");
  for(int i = 0; i < (int)userScore.size(); i++)
  {
    strcpy(temp, userScore[i].second.c_str());
    fprintf(highScoreData, "%s %d\n", temp, userScore[i].first);
  }
  fclose(highScoreData);
}

void DwindlingGalaxies::displayHighScore()
{
  Font highScoreText;
  vector<pair<int, string>> userScore;
  FILE* highScoreData;
  int   highScore[11];
  char  temp[255];
  string name[11];

  if(!highScoreText.loadFromFile("Fonts/Future_Now.ttf"))
  {
    cout << "High Score Font Not Found" << endl;
    exit(0);
  }

  // Read Scores from File.
  highScoreData = fopen("Scores/highScores.txt", "r");
  for(int i = 0; i < 11; i++)
  {
    fscanf(highScoreData, "%s", temp);
    name[i] = temp;
    fscanf(highScoreData, "%d", &highScore[i]);
    userScore.push_back(make_pair(highScore[i], name[i]));
  }

  // Draw Each Valid Entry — Skip Nulls.
  for(int i = 0; i < 11; i++)
  {
    if(userScore[i].second == "null" && userScore[i].first == 0) continue;

    // Ensure Scores Follow the Camera's Viewport.
    if(player->get_x() > WindowSize.x * 1.5)
    {
      showHighScore((1.5 * WindowSize.x) - 210, (WindowSize.y / 2 - 235) + (50 * i), userScore[i].second, win, &highScoreText);
      showHighScore((1.5 * WindowSize.x) + 130, (WindowSize.y / 2 - 235) + (50 * i), to_string(userScore[i].first), win, &highScoreText);
    }
    else if(player->get_x() < WindowSize.x * -0.5)
    {
      showHighScore((-0.5 * WindowSize.x) - 210, (WindowSize.y / 2 - 235) + (50 * i), userScore[i].second, win, &highScoreText);
      showHighScore((-0.5 * WindowSize.x) + 130, (WindowSize.y / 2 - 235) + (50 * i), to_string(userScore[i].first), win, &highScoreText);
    }
    else
    {
      showHighScore(player->get_x() - 210, (WindowSize.y / 2 - 235) + (50 * i), userScore[i].second, win, &highScoreText);
      showHighScore(player->get_x() + 130, (WindowSize.y / 2 - 235) + (50 * i), to_string(userScore[i].first), win, &highScoreText);
    }
  }

  fclose(highScoreData);
}

void DwindlingGalaxies::showHighScore(int x, int y, string word, RenderWindow* window, Font* font)
{
  Text scoreText;
  scoreText.setFont(*font);
  scoreText.setPosition(x, y);
  scoreText.setString(word);
  scoreText.setCharacterSize(40);
  win->draw(scoreText);
}
// ------------------------------------------------------------------------------


// ------------------------------------------------------------------------------
// -                       P O W E R - U P   L O G I C -
// ------------------------------------------------------------------------------
void DwindlingGalaxies::initPowerUps()
{
  spawnTimerMaxPU = 150.f;
  spawnTimerPU    = spawnTimerMaxPU;
}

void DwindlingGalaxies::updatePowerUps()
{
  // Increment Timer Based on Dynamic Difficulty Setting.
  spawnTimerPU += powerUpSpawnTimer;
  unsigned counter = 0;

  // Alternate Between FasterFiring & ExtraLive Spawns.
  if(switchOn == true)
  {
    // Calculate Random Horizontal Position Across the Wide World Space.
    if(spawnTimerPU >= spawnTimerMaxPU)
    {
      powerUps.push_back(new FasterFiring(rand() % WindowSize.x * 3.f - WindowSize.x, -20.f));
      spawnTimerPU = 0.f;
      switchOn = false;
    }
  }
  if(switchOn == false)
  {
    // Calculate Random Horizontal Position Across the Wide World Space.
    if(spawnTimerPU >= spawnTimerMaxPU)
    {
      powerUps.push_back(new ExtraLive(rand() % WindowSize.x * 3.f - WindowSize.x, -20.f));
      spawnTimerPU = 0.f;
      switchOn = true;
    }
  }

  // Process All Active Power-Ups.
  for(auto *PowerUp : powerUps)
  {
    PowerUp->update();
    
    // Remove Items that Fall Past the Bottom Boundary.
    if(PowerUp->getBounds().top > WindowSize.y)
    {
      delete powerUps.at(counter);
      powerUps.erase(powerUps.begin() + counter);
      --counter;
    }
    
    // Check if Player Intersects Power-Up.
    else if(PowerUp->getBounds().intersects(player->getBounds()))
    {
      powerUpSound.play();
      score += 100;

      // Resolve Specific Effect Based on PowerUp Type.
      if(PowerUp->powerUpEffect() == 1)
      {
        // Extra Life Effect (Capped at 5).
        num_lives++;
        if(num_lives > 5) num_lives = 5;
      }
      else
      {
        // Faster Firing Effect (Increases Available Shots/Fire Rate).
        shots = shots + PowerUp->powerUpEffect();
      }

      // Cleanup Power-Up After Collection.
      delete powerUps.at(counter);
      powerUps.erase(powerUps.begin() + counter);
      --counter;
    }
    
    ++counter;
  }
}
// ------------------------------------------------------------------------------


// ------------------------------------------------------------------------------
// -                          A L I E N   L O G I C -
// ------------------------------------------------------------------------------
void DwindlingGalaxies::initAliens()
{
  // Sets Baseline Timers for Enemy Spawning.
  spawnTimerMax = 100.f;
  spawnTimer    = spawnTimerMax;
}

void DwindlingGalaxies::updateAliens()
{
  // Increment Spawn Timer Based on Difficulty/Level Variables.
  spawnTimer += alienSpawnTimer;
  unsigned counter = 0;

  // Cycle Spawn Order: Talz -> MondoShawn -> Helghast.
  if(alienSwitch == true)
  {
    if(spawnTimer >= spawnTimerMax)
    {
      aliens.push_back(new Talz(rand() % WindowSize.x * 3.f - WindowSize.x, WindowSize.y));
      spawnTimer   = 0.f;
      alienSwitch  = false;
    }
  }
  else if(alienSwitch == false && helghastOn == false)
  {
    if(spawnTimer >= spawnTimerMax)
    {
      aliens.push_back(new MondoShawn(rand() % WindowSize.x * 3.f - WindowSize.x, 0));
      spawnTimer   = 0.f;
      alienSwitch  = true;
      helghastOn   = true;
    }
  }
  else if(helghastOn == true && alienSwitch == false)
  {
    if(spawnTimer >= spawnTimerMax)
    {
      aliens.push_back(new Helghast(rand() % WindowSize.x * 3.f - WindowSize.x, 0));
      spawnTimer  = 0.f;
      helghastOn  = false;
    }
  }

  // Process All Active Aliens.
  for(auto *alien : aliens)
  {
    alien->update();

    // Remove Aliens that Fall Past the Bottom Boundary.
    if(alien->getBounds().top > WindowSize.y)
    {
      delete aliens.at(counter);
      aliens.erase(aliens.begin() + counter);
      --counter;
    }

    // Penalise Score, Reduce Life, and Reset Player Position.
    else if(alien->getBounds().intersects(player->getBounds()))
    {
      explosion.play();
      score -= 100;
      if(score < 0) score = 0;

      delete aliens.at(counter);
      aliens.erase(aliens.begin() + counter);
      --counter;

      // Respawn Mechanics.
      teleport.play();
      player->set_position(Vector2f(WindowSize.x / 2, WindowSize.y / 2));

      // Clear All Active Projectiles to Prevent "Ghost" Hits Upon Respawn.
      for(auto* laser : lasers) delete laser;
      lasers.clear();
      num_lives -= 1;
    }
    
    ++counter;
  }
}

void DwindlingGalaxies::updateCombat()
{
  // Checks for Intersections Between Lasers & Aliens.
  for(int i = 0; i < (int)aliens.size(); ++i)
  {
    bool isAlive = false;

    // Nested Loop to Check Every Active Laser Against Every Active Alien.
    for(size_t k = 0; k < lasers.size() && isAlive == false; k++)
    {
      // AABB Intersection Check for Hits.
      if(aliens[i]->getBounds().intersects(lasers[k]->getBounds()))
      {
        // Add Variable Points Based on Alien Type.
        explosion.play();
        score += aliens[i]->getPoints();

        // Clean-Up Destroyed Entities.
        delete aliens[i];
        aliens.erase(aliens.begin() + i);
        delete lasers[k];
        lasers.erase(lasers.begin() + k);

        // Break Inner Loop to Prevent Accessing Deleted Alien.
        isAlive = true;
      }
    }
  }
}
// ------------------------------------------------------------------------------


// ------------------------------------------------------------------------------
// -                     P L A Y E R   C O N T R O L S -
// ------------------------------------------------------------------------------
void DwindlingGalaxies::keyboardControls()
{
  // Aggregate All Menu States to Determine if Gameplay Inputs Should be Ignored.
  bool inMenu = menu.get_title()    || menu.get_menu()      || menu.get_error()   ||
                menu.get_highScore()|| menu.get_options()   || menu.get_controls()||
                menu.get_about()    || menu.get_quit()      || menu.get_pause()   ||
                menu.get_confirm()  || menu.get_gameOverMenu() || menu.get_easy() ||
                menu.get_medium()   || menu.get_expert(); 
    
  // Run Menu Check.
  if(!inMenu)
  {
    // Ensures Smooth 8-way Movement by Handling Dual-Key Presses Before Single-Direction Inputs.
    if (Keyboard::isKeyPressed(Keyboard::Left)  && Keyboard::isKeyPressed(Keyboard::Up))   
    { 
      player->move_left(6, WindowSize);  
      player->move_up(6, WindowSize); 
    }
    else if(Keyboard::isKeyPressed(Keyboard::Left)  && Keyboard::isKeyPressed(Keyboard::Down)) 
    { 
      player->move_left(6, WindowSize);  
      player->move_down(6, WindowSize); 
    }
    else if(Keyboard::isKeyPressed(Keyboard::Right) && Keyboard::isKeyPressed(Keyboard::Up))   
    { 
      player->move_right(6, WindowSize);
      player->move_up(6, WindowSize); 
    }
    else if(Keyboard::isKeyPressed(Keyboard::Right) && Keyboard::isKeyPressed(Keyboard::Down)) 
    { 
      player->move_right(6, WindowSize); 
      player->move_down(6, WindowSize);
    }

    // Single Directional Movement.
    else if(Keyboard::isKeyPressed(Keyboard::Right)) 
    {
      player->move_right(6, WindowSize); 
    }
    else if(Keyboard::isKeyPressed(Keyboard::Left))  
    {
      player->move_left(6, WindowSize); 
    }
    else if(Keyboard::isKeyPressed(Keyboard::Up))    
    { 
      player->move_up(6, WindowSize);
    }
    else if(Keyboard::isKeyPressed(Keyboard::Down))  
    { 
      player->move_down(6, WindowSize); 
    }

    // Laser Firing Logic.
    const int MAX_LASERS = 50;
    static Clock laserCooldown;
    if(shots < 0) shots = 0;

    // Spacebar Input for Laser Firing.
    if(Keyboard::isKeyPressed(Keyboard::Space))
    {
      // Dynamic Cooldown: 100ms if Power-Up is Available, 400ms Otherwise.
      int cooldownTime = (shots > 0) ? 100 : 400;
      if(laserCooldown.getElapsedTime().asMilliseconds() >= cooldownTime)
      {
        // Spawn Laser at Player Coordinates with Slight Offset (+4) for Alignment.
        if((int)lasers.size() < MAX_LASERS)
        {
          // Facing Right.
          if(player->get_facingDirection() == true)
            lasers.push_back(new Laser(player->get_x(), player->get_y() + 4,  12.f, 0.f, 1.f));
          // Facing Left.
          else
            lasers.push_back(new Laser(player->get_x(), player->get_y() + 4, -12.f, 0.f, 1.f));
          
          // Consume Power-Up Shot if Applicable.
          laser_sound.play();
          if(shots > 0) shots--;
          laserCooldown.restart();
        }
      }
    }
  }

  // System Commands: Immediate Quit Prompt.
  if(Keyboard::isKeyPressed(Keyboard::Escape)) menu.set_quit(true);
  
  // Pause Toggle (Disabled if Game is in Game Over State).
  if(!(menu.get_gameOver() == true && num_lives == 0))
  {
    if(Keyboard::isKeyPressed(Keyboard::P)) menu.set_pause(true);
  }
}
// ------------------------------------------------------------------------------


// ------------------------------------------------------------------------------
// -                    G A M E   L O O P   &   R E S T A R T -
// ------------------------------------------------------------------------------
void DwindlingGalaxies::restartGame()
{
  if(restart == true)
  {
    // Reset Primary Gameplay Variables.
    score     = 0;
    level     = 1;
    num_lives = 3;
    shots     = 0;
    
    // Return Player to the Centere of the Screen.
    player->set_position(Vector2f(WindowSize.x / 2, WindowSize.y / 2));
    
    // Delete All Heap-Allocated Entities to Prevent Memory Leaks.
    for(auto* laser   : lasers)   delete laser;
    for(auto* alien   : aliens)   delete alien;
    for(auto* powerUp : powerUps) delete powerUp;

    // Clear Pointers from Vectors.
    lasers.clear();
    aliens.clear();
    powerUps.clear();

    // Reset the Restart Trigger.
    restart = false;
  }

  // Triggered when the Player has Exhausted All Lives.
  if(num_lives == 1) menu.set_gameOver(true);
}

void DwindlingGalaxies::run()
{
  // Start the Background Music Tracks.
  music();

  // Set Button Click Sound.
  menu.setClickSound(&clickSound);

  // Main Window Loop.
  while(win->isOpen())
  {
    Event event;

    // Poll for Window Events.
    while(win->pollEvent(event))
    {
      if(event.type == Event::Closed)
      { 
        win->close(); 
      }
    }

    // Delegate Input Handling to the Controls Module.
    keyboardControls();

    // Logic & State Updates.
    updateMusic();
    updateDifficulty();
    restartGame();

    // Rendering Pipeline.
    win->clear();
    runMenu();
    win->display();
  }
}
// ------------------------------------------------------------------------------

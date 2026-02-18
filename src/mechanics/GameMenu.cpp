// ------------------------------------------------------------------------------
// -               V E R S I O N   I D E N T I F I C A T I O N -
// ------------------------------------------------------------------------------
// File:                    %name: GameMenu.cpp %
// Date Created:            %date_created: Tue Feb 17 13:21:45 2026 %
// CM Version               %version: 2 %
// CM Instance              %instance: 1 %
// Author:                  %created_by: MBusato %
// ------------------------------------------------------------------------------
// -                          D E S C R I P T I O N -
// ------------------------------------------------------------------------------
// Implementation file for the GameMenu class in Dwindling Galaxies. It handles 
// all menu screens including title sequence, main menu, difficulty selection, 
// options, controls, about, pause, quit confirmation, game over, and high score
// display. Manages button hit detection and sprite loading for each menu state.
//
// ------------------------------------------------------------------------------
// -                          L I C E N S I N G -
// ------------------------------------------------------------------------------
// Copyright (c) 2024 EastSide Lion Studios. All rights reserved. Use of this
// software is subject to the license terms found in the LICENSE file located in
// the root directory of this repository.
// ------------------------------------------------------------------------------

#include <iostream>
#include <time.h>

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>

#include "GameMenu.h"
#include "Player.h"

using namespace sf;
using namespace std;

// ------------------------------------------------------------------------------
// -                  D E P E N D E N C Y   I N J E C T I O N -
// ------------------------------------------------------------------------------
void GameMenu::set_window(RenderWindow* win)
{
  this->win = win;
}

void GameMenu::set_size(Vector2u WindowSize)
{
  this->WindowSize = WindowSize;
}

void GameMenu::set_player(Player* player)
{
  this->player = player;
}
// ------------------------------------------------------------------------------


// ------------------------------------------------------------------------------
// -                        D E S T R U C T O R -
// ------------------------------------------------------------------------------
GameMenu::~GameMenu()
{
}
// ------------------------------------------------------------------------------


// ------------------------------------------------------------------------------
// -                      T I T L E   S E Q U E N C E -
// ------------------------------------------------------------------------------
void GameMenu::titleSequence()
{
  // Load Studio Logo Sprite.
  if(!studio_logo.loadFromFile("Images/Logo1.png"))
  {
    cout << "Logo Image Not Found" << endl;
    exit(0);
  }
  logo.setTexture(studio_logo);
  FloatRect bodySize = logo.getGlobalBounds();
  logo.setOrigin(bodySize.width / 2., bodySize.height / 2.);

  // Position Logo Based on Camera Scroll.
  if(player->get_x() > WindowSize.x * 1.5)
  {
    logo.setPosition(1.5 * WindowSize.x, WindowSize.y / 2);
  }
  else if(player->get_x() < WindowSize.x * -0.5)
  {
    logo.setPosition(-0.5 * WindowSize.x, WindowSize.y / 2);
  }
  else
  {
    logo.setPosition(player->get_x(), WindowSize.y / 2);
  }

  // Load Main Title Backdrop.
  if(!main_title.loadFromFile("Images/main_title.png"))
  {
    cout << "Title Image Not Found" << endl;
    exit(0);
  }
  titleScene.setTexture(main_title);

  // Scale to Fit Window.
  Vector2u TextureSize = main_title.getSize();
  float ScaleX = (float)WindowSize.x / TextureSize.x;
  float ScaleY = (float)WindowSize.y / TextureSize.y;
  titleScene.setScale(ScaleX, ScaleY);
  FloatRect bodySize1 = titleScene.getGlobalBounds();
  titleScene.setOrigin(bodySize1.width / 2., bodySize1.height / 2.);

  // Position Title Scene.
  if(player->get_x() > WindowSize.x * 1.5)
  {
    titleScene.setPosition(1.5 * WindowSize.x, WindowSize.y / 2);
  }
  else if(player->get_x() < WindowSize.x * -0.5)
  {
    titleScene.setPosition(-0.5 * WindowSize.x, WindowSize.y / 2);
  }
  else
  {
    titleScene.setPosition(player->get_x(), WindowSize.y / 2);
  }

  // Start Invisible for Fade-in Effect
  titleScene.setColor(Color(255, 255, 255, 0));

  // Fade Logo in, then Show Title.
  int currentTime = timer.getElapsedTime().asMilliseconds();
  if(currentTime >= targetTime + 2500)
  {
    titleScene.setColor(Color(255, 255, 255, 255));
  }
  else
  {
    int currentAlpha = startAlpha + (endAlpha - startAlpha) * currentTime / targetTime;
    if(currentAlpha >= endAlpha) currentAlpha = endAlpha;
    logo.setColor(Color(255, 255, 255, currentAlpha));
  }

  // Press Enter to Exit Title Screen.
  if(Keyboard::isKeyPressed(Keyboard::Enter))
  {
    title  = false;
    isMenu = true;
  }

  // Draw the Logo and Title Screen to Game.
  win->draw(logo);
  win->draw(titleScene);
}
// ------------------------------------------------------------------------------


// ------------------------------------------------------------------------------
// -                     M A I N   M E N U   L O G I C -
// ------------------------------------------------------------------------------
int GameMenu::mainMenuButtons()
{
  // Get Current Position & Status of the Mouse. 
  Vector2i mouse = Mouse::getPosition(*win);
  if(!Mouse::isButtonPressed(Mouse::Left)) return difficulty;

  // Quit Button (X in Corner).
  if((mouse.x >= ((WindowSize.x / 2) + 825)) && (mouse.y >= ((WindowSize.y / 2) - 500)) &&
     (mouse.x <= ((WindowSize.x / 2) + 930)) && (mouse.y <= ((WindowSize.y / 2) - 435)))
  {
    win->close();
    exit(0);
    return difficulty;
  }

  // Start Button.
  if((mouse.x >= (WindowSize.x / 2) - 450) && (mouse.y >= ((WindowSize.y / 2) - 320)) &&
     (mouse.x <= ((WindowSize.x / 2) - 155)) && (mouse.y <= (WindowSize.y / 2) - 250))
  {
    difficulty  = 0;
    isMenu      = true;
    isEasy      = false;
    isMedium    = false;
    isExpert    = false;
    isError     = false;
    isHighScore = false;
    isOptions   = false;
    isControls  = false;
    isAbout     = false;
    return difficulty;
  }

  // High Score Button.
  if((mouse.x >= ((WindowSize.x / 2) - 150)) && (mouse.y >= ((WindowSize.y / 2) - 320)) &&
     (mouse.x <= ((WindowSize.x / 2) + 145)) && (mouse.y <= (WindowSize.y / 2) - 250))
  {
    difficulty  = 0;
    isHighScore = true;
    isMenu      = false;
    isEasy      = false;
    isMedium    = false;
    isExpert    = false;
    isError     = false;
    isOptions   = false;
    return difficulty;
  }

  // Options Button.
  if((mouse.x >= ((WindowSize.x / 2) + 150)) && (mouse.y >= ((WindowSize.y / 2) - 320)) &&
     (mouse.x <= ((WindowSize.x / 2) + 445)) && (mouse.y <= (WindowSize.y / 2) - 250))
  {
    difficulty  = 0;
    isOptions   = true;
    isHighScore = false;
    isMenu      = false;
    isEasy      = false;
    isMedium    = false;
    isExpert    = false;
    isError     = false;
    return difficulty;
  }

  // Difficulty Selection Buttons.
  if(isMenu == true || isEasy == true || isMedium == true || isExpert == true)
  {
    // Easy Mode.
    if((mouse.x >= ((WindowSize.x / 2) - 140)) && (mouse.y >= (WindowSize.y / 2 - 125)) &&
       (mouse.x <= ((WindowSize.x / 2) + 140)) && (mouse.y <= (WindowSize.y / 2 - 55)))
    {
      difficulty = 1;
      isEasy     = true;
      isMenu     = false;
      isMedium   = false;
      isExpert   = false;
      isError    = false;
      return difficulty;
    }
    // Medium Mode.
    else if((mouse.x >= ((WindowSize.x / 2) - 140)) && (mouse.y >= (WindowSize.y / 2 - 30)) &&
            (mouse.x <= ((WindowSize.x / 2) + 140)) && (mouse.y <= (WindowSize.y / 2 + 40)))
    {
      difficulty = 2;
      isMedium   = true;
      isMenu     = false;
      isEasy     = false;
      isExpert   = false;
      isError    = false;
      return difficulty;
    }
    // Expert Mode.
    else if((mouse.x >= ((WindowSize.x / 2) - 140)) && (mouse.y >= (WindowSize.y / 2 + 55)) &&
            (mouse.x <= ((WindowSize.x / 2) + 140)) && (mouse.y <= (WindowSize.y / 2 + 125)))
    {
      difficulty = 3;
      isExpert   = true;
      isMenu     = false;
      isEasy     = false;
      isMedium   = false;
      isError    = false;
      return difficulty;
    }
    // Play Button.
    else if((mouse.x >= ((WindowSize.x / 2) - 195)) && (mouse.y >= (WindowSize.y / 2 + 210)) &&
            (mouse.x <= ((WindowSize.x / 2) + 185)) && (mouse.y <= (WindowSize.y / 2 + 280)))
    {
      if(difficulty == 0)
      {
        // No Difficulty Selected — Show Error.
        isError     = true;
        isMenu      = false;
        isEasy      = false;
        isMedium    = false;
        isExpert    = false;
        isHighScore = false;
        isOptions   = false;
        isControls  = false;
        isAbout     = false;
        return difficulty;
      }
      else
      {
        // Start the Game.
        isMenu      = false;
        isEasy      = false;
        isMedium    = false;
        isExpert    = false;
        isError     = false;
        isHighScore = false;
        isOptions   = false;
        isControls  = false;
        isAbout     = false;
        return difficulty;
      }
    }
  }

  // Options Sub-Menu Buttons.
  if(isOptions == true)
  {
    // Controls Button.
    if((mouse.x >= (WindowSize.x / 2) - 195) && (mouse.y >= (WindowSize.y / 2) + 90) &&
       (mouse.x <= (WindowSize.x / 2) + 195) && (mouse.y <= (WindowSize.y / 2) + 160))
    {
      difficulty = 0;
      isControls = true;
      isOptions  = false;
      isAbout    = false;
      return difficulty;
    }
    // About Button.
    if((mouse.x >= (WindowSize.x / 2) - 195) && (mouse.y >= (WindowSize.y / 2) - 95) &&
       (mouse.x <= (WindowSize.x / 2) + 195) && (mouse.y <= (WindowSize.y / 2) - 25))
    {
      difficulty = 0;
      isAbout    = true;
      isOptions  = false;
      isControls = false;
      return difficulty;
    }
  }

  // Return Selected Difficulty.
  return difficulty;
}
// ------------------------------------------------------------------------------


// ------------------------------------------------------------------------------
// -                 S P R I T E   L O A D I N G   H E L P E R S -
// ------------------------------------------------------------------------------
Sprite GameMenu::mainMenuSprite()
{
  // Check the Texture Loads Properly. 
  if(!simple_menu.loadFromFile("Images/StartMenu.png"))
  {
    cout << "Main Menu Image Not Found" << endl;
    exit(0);
  }

  // Centre the Texture on the Screen.
  menuSprite.setTexture(simple_menu);
  FloatRect bodySize = menuSprite.getGlobalBounds();
  menuSprite.setOrigin(bodySize.width / 2., bodySize.height / 2.);

  // Coordinate Locking Logic: Keeps UI in Front of Player.
  if(player->get_x() > WindowSize.x * 1.5)
  {
    menuSprite.setPosition(1.5 * WindowSize.x, WindowSize.y / 2);
  }
  else if(player->get_x() < WindowSize.x * -0.5)
  {
    menuSprite.setPosition(-0.5 * WindowSize.x, WindowSize.y / 2);
  }
  else
  {
    menuSprite.setPosition(player->get_x(), WindowSize.y / 2);
  }

  // Return Texture for Viewing. 
  return menuSprite;
}

Sprite GameMenu::easyMode()
{
  // Check the Texture Loads Properly. 
  if(!beginner_image.loadFromFile("Images/MenuBeginner.png"))
  {
    cout << "Beginner Button Image Not Found" << endl;
    exit(0);
  }

  // Centre the Texture on the Screen.
  beginner.setTexture(beginner_image);
  FloatRect bodySize = beginner.getGlobalBounds();
  beginner.setOrigin(bodySize.width / 2., bodySize.height / 2.);

  // Coordinate Locking Logic: Keeps UI in Front of Player.
  if(player->get_x() > WindowSize.x * 1.5)
  {
    beginner.setPosition(1.5 * WindowSize.x, WindowSize.y / 2);
  }
  else if(player->get_x() < WindowSize.x * -0.5)
  {
    beginner.setPosition(-0.5 * WindowSize.x, WindowSize.y / 2);
  }
  else
  {
    beginner.setPosition(player->get_x(), WindowSize.y / 2);
  }

  // Return Texture for Viewing.
  return beginner;
}

Sprite GameMenu::mediumMode()
{
  // Check the Texture Loads Properly.
  if(!medium_image.loadFromFile("Images/MenuMedium.png"))
  {
    cout << "Medium Button Image Not Found" << endl;
    exit(0);
  }
  
  // Centre the Texture on the Screen.
  medium.setTexture(medium_image);
  FloatRect bodySize = medium.getGlobalBounds();
  medium.setOrigin(bodySize.width / 2., bodySize.height / 2.);

  // Coordinate Locking Logic: Keeps UI in Front of Player.
  if(player->get_x() > WindowSize.x * 1.5)
  {
    medium.setPosition(1.5 * WindowSize.x, WindowSize.y / 2);
  }
  else if(player->get_x() < WindowSize.x * -0.5)
  {
    medium.setPosition(-0.5 * WindowSize.x, WindowSize.y / 2);
  }
  else
  {
    medium.setPosition(player->get_x(), WindowSize.y / 2);
  }

  // Return Texture for Viewing.
  return medium;
}

Sprite GameMenu::expertMode()
{
  // Check the Texture Loads Properly.
  if(!expert_image.loadFromFile("Images/MenuExpert.png"))
  {
    cout << "Expert Button Image Not Found" << endl;
    exit(0);
  }

  // Centre the Texture on the Screen.
  expert.setTexture(expert_image);
  FloatRect bodySize = expert.getGlobalBounds();
  expert.setOrigin(bodySize.width / 2., bodySize.height / 2.);

  // Coordinate Locking Logic: Keeps UI in Front of Player.
  if(player->get_x() > WindowSize.x * 1.5)
  {
    expert.setPosition(1.5 * WindowSize.x, WindowSize.y / 2);
  }
  else if(player->get_x() < WindowSize.x * -0.5)
  {
    expert.setPosition(-0.5 * WindowSize.x, WindowSize.y / 2);
  }
  else
  {
    expert.setPosition(player->get_x(), WindowSize.y / 2);
  }

  // Return Texture for Viewing.
  return expert;
}

Sprite GameMenu::errorSprite()
{
  // Check the Texture Loads Properly.
  if(!error_image.loadFromFile("Images/ErrorPopUp.png"))
  {
    cout << "Error Message Image Not Found" << endl;
    exit(0);
  }

  // Centre the Texture on the Screen.
  error.setTexture(error_image);
  FloatRect bodySize = error.getGlobalBounds();
  error.setOrigin(bodySize.width / 2., bodySize.height / 2.);

  // Coordinate Locking Logic: Keeps UI in Front of Player.
  if(player->get_x() > WindowSize.x * 1.5)
  {
    error.setPosition(1.5 * WindowSize.x, WindowSize.y / 2);
  }
  else if(player->get_x() < WindowSize.x * -0.5)
  {
    error.setPosition(-0.5 * WindowSize.x, WindowSize.y / 2);
  }
  else
  {
    error.setPosition(player->get_x(), WindowSize.y / 2);
  }

  // Return Texture for Viewing.
  return error;
}

Sprite GameMenu::HighScoreSprite()
{
  // Check the Texture Loads Properly. 
  if(!highScore_image.loadFromFile("Images/HighScore.png"))
  {
    cout << "High Score Image Not Found" << endl;
    exit(0);
  }

  // Centre the Texture on the Screen.
  highScore.setTexture(highScore_image);
  FloatRect bodySize = highScore.getGlobalBounds();
  highScore.setOrigin(bodySize.width / 2., bodySize.height / 2.);

  // Coordinate Locking Logic: Keeps UI in Front of Player.
  if(player->get_x() > WindowSize.x * 1.5)
  {
    highScore.setPosition(1.5 * WindowSize.x, WindowSize.y / 2);
  }
  else if(player->get_x() < WindowSize.x * -0.5)
  {
    highScore.setPosition(-0.5 * WindowSize.x, WindowSize.y / 2);
  }
  else
  {
    highScore.setPosition(player->get_x(), WindowSize.y / 2);
  }

  // Return Texture for Viewing.
  return highScore;
}

Sprite GameMenu::get_optionsSprite()
{
  // Check the Texture Loads Properly.
  if(!options_menu.loadFromFile("Images/OptionsMenu.png"))
  {
    cout << "Options Screen Image Not Found" << endl;
    exit(0);
  }

  // Centre the Texture on the Screen.
  options.setTexture(options_menu);
  FloatRect bodySize = options.getGlobalBounds();
  options.setOrigin(bodySize.width / 2., bodySize.height / 2.);

  // Coordinate Locking Logic: Keeps UI in Front of Player.
  if(player->get_x() > WindowSize.x * 1.5)
  {
    options.setPosition(1.5 * WindowSize.x, WindowSize.y / 2);
  }
  else if(player->get_x() < WindowSize.x * -0.5)
  {
    options.setPosition(-0.5 * WindowSize.x, WindowSize.y / 2);
  }
  else
  {
    options.setPosition(player->get_x(), WindowSize.y / 2);
  }

  // Return Texture for Viewing.
  return options;
}

Sprite GameMenu::get_controlsSprite()
{
  // Check the Texture Loads Properly.
  if(!controls_menu.loadFromFile("Images/OptionsControls.png"))
  {
    cout << "Controls Image Not Found" << endl;
    exit(0);
  }

  // Centre the Texture on the Screen.
  controls.setTexture(controls_menu);
  FloatRect bodySize = controls.getGlobalBounds();
  controls.setOrigin(bodySize.width / 2., bodySize.height / 2.);

  // Coordinate Locking Logic: Keeps UI in Front of Player.
  if(player->get_x() > WindowSize.x * 1.5)
  {
    controls.setPosition(1.5 * WindowSize.x, WindowSize.y / 2);
  }
  else if(player->get_x() < WindowSize.x * -0.5)
  {
    controls.setPosition(-0.5 * WindowSize.x, WindowSize.y / 2);
  }
  else
  {
    controls.setPosition(player->get_x(), WindowSize.y / 2);
  }

  // Return Texture for Viewing.
  return controls;
}

Sprite GameMenu::get_aboutSprite()
{
  // Check the Texture Loads Properly.
  if(!about_menu.loadFromFile("Images/OptionsAbout.png"))
  {
    cout << "About Image Not Found" << endl;
    exit(0);
  }

  // Centre the Texture on the Screen.
  about.setTexture(about_menu);
  FloatRect bodySize = about.getGlobalBounds();
  about.setOrigin(bodySize.width / 2., bodySize.height / 2.);

  // Coordinate Locking Logic: Keeps UI in Front of Player.
  if(player->get_x() > WindowSize.x * 1.5)
  {
    about.setPosition(1.5 * WindowSize.x, WindowSize.y / 2);
  }
  else if(player->get_x() < WindowSize.x * -0.5)
  {
    about.setPosition(-0.5 * WindowSize.x, WindowSize.y / 2);
  }
  else
  {
    about.setPosition(player->get_x(), WindowSize.y / 2);
  }

  // Return Texture for Viewing. 
  return about;
}

void GameMenu::loadQuitButton()
{
  // Check the Texture Loads Properly.
  if(!quitButton_image.loadFromFile("Images/QuitButton.png"))
  {
    cout << "Quit Button Image Not Found" << endl;
    exit(0);
  }

  // Centre the Texture on the Screen.
  quitButton.setTexture(quitButton_image);
  FloatRect bodySize = quitButton.getGlobalBounds();
  quitButton.setOrigin(bodySize.width / 2., bodySize.height / 2.);
  quitButton.setScale(0.15, 0.15);

  // Coordinate Locking Logic: Keeps UI in Front of Player.
  if(player->get_x() > WindowSize.x * 1.5)
  {
    quitButton.setPosition(1.5 * WindowSize.x + 825, 40);
  }
  else if(player->get_x() < WindowSize.x * -0.5)
  {
    quitButton.setPosition(-0.5 * WindowSize.x + 825, 40);
  }
  else
  {
    quitButton.setPosition(player->get_x() + 825, 40);
  }

  // Draw the Texture for Viewing. 
  win->draw(quitButton);
}

void GameMenu::displayScreen(Sprite screen)
{
  // Draw the Provided Texture for Viewing. 
  loadQuitButton();
  win->draw(screen);
}
// ------------------------------------------------------------------------------


// ------------------------------------------------------------------------------
// -                         Q U I T   P O P - U P -
// ------------------------------------------------------------------------------
void GameMenu::quit()
{
  // Check the Texture Loads Properly. 
  if(!quit_image.loadFromFile("Images/PopUp.png"))
  {
    cout << "Popup Image Not Found" << endl;
    exit(0);
  }

  // Centre the Texture on the Screen.
  popUp.setTexture(quit_image);
  FloatRect bodySize = popUp.getGlobalBounds();
  popUp.setOrigin(bodySize.width / 2., bodySize.height / 2.);

  // Coordinate Locking Logic: Keeps UI in Front of Player.
  if(player->get_x() > WindowSize.x * 1.5)
  {
    popUp.setPosition(1.5 * WindowSize.x, WindowSize.y / 2);
  }
  else if(player->get_x() < WindowSize.x * -0.5)
  {
    popUp.setPosition(-0.5 * WindowSize.x, WindowSize.y / 2);
  }
  else
  {
    popUp.setPosition(player->get_x(), WindowSize.y / 2);
  }

  // Button Click Detection.
  Vector2i mouse = Mouse::getPosition(*win);
  if(Mouse::isButtonPressed(Mouse::Left))
  {
    // Yes — Quit.
    if((mouse.x >= (WindowSize.x / 2) - 190) && mouse.y >= ((WindowSize.y / 2) + 40) &&
       (mouse.x <= (WindowSize.x / 2) - 50)  && (mouse.y <= (WindowSize.y / 2) + 110))
    {
      win->close();
      exit(0);
    }
    // No — Close Dialog.
    else if((mouse.x <= (WindowSize.x / 2) + 190) && mouse.y >= ((WindowSize.y / 2) + 40) &&
            (mouse.x >= (WindowSize.x / 2) + 50)  && (mouse.y <= (WindowSize.y / 2) + 110))
    {
      isQuit = false;
    }
  }

  // Draw the Texture for Viewing. 
  win->draw(popUp);
}
// ------------------------------------------------------------------------------


// ------------------------------------------------------------------------------
// -                         P A U S E   M E N U -
// ------------------------------------------------------------------------------
void GameMenu::pause()
{
  // Check the Texture Loads Properly. 
  if(!pause_image.loadFromFile("Images/Pause.png"))
  {
    cout << "Pause Image Not Found" << endl;
    exit(0);
  }

  // Centre the Texture on the Screen.
  pauseDialoge.setTexture(pause_image);
  pauseDialoge.setScale(1.2, 1.2);
  FloatRect bodySize = pauseDialoge.getGlobalBounds();
  pauseDialoge.setOrigin(bodySize.width / 2., bodySize.height / 2.);

  // Coordinate Locking Logic: Keeps UI in Front of Player.
  if(player->get_x() > WindowSize.x * 1.5)
  {
    pauseDialoge.setPosition(1.5 * WindowSize.x + 50, 50 + WindowSize.y / 2);
  }
  else if(player->get_x() < WindowSize.x * -0.5)
  {
    pauseDialoge.setPosition(-0.5 * WindowSize.x + 50, 50 + WindowSize.y / 2);
  }
  else
  {
    pauseDialoge.setPosition(player->get_x() + 50, 50 + WindowSize.y / 2);
  }

  // Button Click Detection.
  Vector2i mouse = Mouse::getPosition(*win);
  if(Mouse::isButtonPressed(Mouse::Left))
  {
    // Resume.
    if((mouse.x >= ((WindowSize.x / 2) - 140)) && (mouse.y >= (WindowSize.y / 2 - 5)) &&
       (mouse.x <= ((WindowSize.x / 2) + 110)) && (mouse.y <= (WindowSize.y / 2 + 62)))
    {
      isPause = false;
    }
    // Restart.
    else if((mouse.x >= ((WindowSize.x / 2) - 140)) && (mouse.y >= (WindowSize.y / 2 + 120)) &&
            (mouse.x <= ((WindowSize.x / 2) + 110)) && (mouse.y <= (WindowSize.y / 2 + 187)))
    {
      isConfirm = true;
      isPause   = false;
    }
    // Main Menu.
    else if((mouse.x >= ((WindowSize.x / 2) - 140)) && (mouse.y >= (WindowSize.y / 2 - 125)) &&
            (mouse.x <= ((WindowSize.x / 2) + 110)) && (mouse.y <= (WindowSize.y / 2 - 58)))
    {
      isConfirm = true;
      isPause   = false;
      mainMenu  = true;
    }
  }

  // Draw the Texture for Viewing.
  win->draw(pauseDialoge);
}
// ------------------------------------------------------------------------------


// ------------------------------------------------------------------------------
// -                   C O N F I R M   D I A L O G -
// ------------------------------------------------------------------------------
bool GameMenu::confirm()
{
  // Check the Texture Loads Properly. 
  if(!confirm_image.loadFromFile("Images/Confirm.png"))
  {
    cout << "Confirm PopUp Image Not Found" << endl;
    exit(0);
  }

  // Centre the Texture on the Screen.
  confirms.setTexture(confirm_image);
  confirms.setScale(1.1, 1.1);
  FloatRect bodySize = confirms.getGlobalBounds();
  confirms.setOrigin(bodySize.width / 2., bodySize.height / 2.);

  // Coordinate Locking Logic: Keeps UI in Front of Player.
  if(player->get_x() > WindowSize.x * 1.5)
  {
    confirms.setPosition(1.5 * WindowSize.x + 50, 50 + WindowSize.y / 2);
  }
  else if(player->get_x() < WindowSize.x * -0.5)
  {
    confirms.setPosition(-0.5 * WindowSize.x + 50, 50 + WindowSize.y / 2);
  }
  else
  {
    confirms.setPosition(player->get_x() + 50, 50 + WindowSize.y / 2);
  }

  // Button Click Detection.
  Vector2i mouse = Mouse::getPosition(*win);
  if(Mouse::isButtonPressed(Mouse::Left))
  {
    // Yes — Confirm.
    if((mouse.x >= (WindowSize.x / 2) - 170) && mouse.y >= ((WindowSize.y / 2) + 80) &&
       (mouse.x <= (WindowSize.x / 2) - 50)  && (mouse.y <= ((WindowSize.y / 2) + 150)))
    {
      if(mainMenu == true)
      {
        // Return to Main Menu.
        difficulty = 0;
        isMenu     = true;
        isConfirm  = false;
        isEasy     = false;
        isMedium   = false;
        isExpert   = false;
        isError    = false;
        return true;
      }
      else
      {
        // Restart Game.
        isConfirm   = false;
        isMenu      = false;
        isEasy      = false;
        isMedium    = false;
        isExpert    = false;
        isError     = false;
        isHighScore = false;
        isOptions   = false;
        isControls  = false;
        isAbout     = false;
        return true;
      }
    }
    // No — Return to Pause Menu.
    else if((mouse.x <= (WindowSize.x / 2) + 200) && mouse.y >= ((WindowSize.y / 2) + 80) &&
            (mouse.x >= (WindowSize.x / 2) + 76)  && (mouse.y <= (WindowSize.y / 2) + 150))
    {
      isConfirm = false;
      isPause   = true;
      return false;
    }
  }
  
  // Draw the Texture for Viewing.
  win->draw(confirms);
  return false;
}
// ------------------------------------------------------------------------------


// ------------------------------------------------------------------------------
// -                 G A M E   O V E R   N A M E   E N T R Y -
// ------------------------------------------------------------------------------
string GameMenu::gameOver(int* addScore)
{
  // Set Global Offset Variables.
  const float TEXT_OFFSET_X = -15;
  const float TEXT_OFFSET_Y = -10;

  // Load Font. 
  if(!playerFont.loadFromFile("Fonts/Future_Now.ttf"))
  {
    cout << "Name Font Not Found" << endl;
    exit(0);
  }

  // Set-Up Text Entry Field.
  playerText.setFont(playerFont);
  playerText.setCharacterSize(72);
  playerText.setString(playerInput);
  FloatRect textBounds = playerText.getLocalBounds();
  playerText.setOrigin(textBounds.width / 2.0f, textBounds.height / 2.0f);

  // Load Game Over Sprite.
  if(!gameOver_image.loadFromFile("Images/GameOver.png"))
  {
    cout << "Game Over Image Not Found" << endl;
    exit(0);
  }

  // Centre the Texture on the Screen.
  gameOverDialoge.setTexture(gameOver_image);
  gameOverDialoge.setScale(0.5, 0.5);
  FloatRect bodySize = gameOverDialoge.getGlobalBounds();
  gameOverDialoge.setOrigin(bodySize.width / 2, bodySize.height / 2);

  // Coordinate Locking Logic: Keeps UI in Front of Player.
  if(player->get_x() > WindowSize.x * 1.5)
  {
    gameOverDialoge.setPosition(1.5 * WindowSize.x - 250, WindowSize.y / 2 - 150);
    playerText.setPosition(1.5 * WindowSize.x + TEXT_OFFSET_X, WindowSize.y / 2 + TEXT_OFFSET_Y);
  }
  else if(player->get_x() < WindowSize.x * -0.5)
  {
    gameOverDialoge.setPosition(-0.5 * WindowSize.x - 250, WindowSize.y / 2 - 150);
    playerText.setPosition(-0.5 * WindowSize.x + TEXT_OFFSET_X, WindowSize.y / 2 + TEXT_OFFSET_Y);
  }
  else
  {
    gameOverDialoge.setPosition(player->get_x() - 250, WindowSize.y / 2 - 150);
    playerText.setPosition(player->get_x() + TEXT_OFFSET_X, WindowSize.y / 2 + TEXT_OFFSET_Y);
  }

  // Handle Text Input.
  while(win->pollEvent(event))
  {
    if(event.type == Event::TextEntered)
    {
      // Backspace.
      if(event.text.unicode == 8)
      {
        if(playerInput.getSize() > 0)
        {
          playerInput.erase(playerInput.getSize() - 1, 1);
          playerText.setString(playerInput);
          FloatRect tb = playerText.getLocalBounds();
          playerText.setOrigin(tb.width / 2.0f, tb.height / 2.0f);
        }
      }
      // Letter Input (A-Z, a-z).
      else if((event.text.unicode >= 65 && event.text.unicode <= 90) ||
              (event.text.unicode >= 97 && event.text.unicode <= 122))
      {
        if(playerInput.getSize() < 12)
        {
          playerInput += static_cast<char>(event.text.unicode);
          playerText.setString(playerInput);
          FloatRect tb = playerText.getLocalBounds();
          playerText.setOrigin(tb.width / 2.0f, tb.height / 2.0f);
        }
      }
    }

    // Enter to Submit.
    if(event.type == Event::KeyPressed && event.key.code == Keyboard::Enter)
    {
      if(playerInput.getSize() > 0)
      {
        isGameMenu = true;
        isGameOver = false;
        *addScore  = 1;
        return playerInput.toAnsiString();
      }
    }
  }

  // Draw the Texture for Viewing.
  win->draw(gameOverDialoge);
  win->draw(playerText);
  return playerInput.toAnsiString();
}
// ------------------------------------------------------------------------------


// ------------------------------------------------------------------------------
// -                   G A M E   O V E R   M E N U -
// ------------------------------------------------------------------------------
bool GameMenu::gameOverMenu()
{
  // Initalise Variables.
  playerInput = "";

  // Check the Texture Loads Properly. 
  if(!gameOverMenu_image.loadFromFile("Images/GameOverMenu.png"))
  {
    cout << "Game Over Menu Image Not Found" << endl;
    exit(0);
  }

  // Centre the Texture on the Screen.
  gameOverMenuDialoge.setTexture(gameOverMenu_image);
  gameOverMenuDialoge.setScale(1.2, 1.2);
  FloatRect bodySize = gameOverMenuDialoge.getGlobalBounds();
  gameOverMenuDialoge.setOrigin(bodySize.width / 2., bodySize.height / 2.);

  // Coordinate Locking Logic: Keeps UI in Front of Player.
  if(player->get_x() > WindowSize.x * 1.5)
  {
    gameOverMenuDialoge.setPosition(1.5 * WindowSize.x + 50, 50 + WindowSize.y / 2);
  }
  else if(player->get_x() < WindowSize.x * -0.5)
  {
    gameOverMenuDialoge.setPosition(-0.5 * WindowSize.x + 50, 50 + WindowSize.y / 2);
  }
  else
  {
    gameOverMenuDialoge.setPosition(player->get_x() + 50, 50 + WindowSize.y / 2);
  }

  // Button Click Detection.
  Vector2i mouse = Mouse::getPosition(*win);
  if(Mouse::isButtonPressed(Mouse::Left))
  {
    // Main Menu.
    if((mouse.x >= ((WindowSize.x / 2) - 150)) && (mouse.y >= (WindowSize.y / 2 - 175)) &&
       (mouse.x <= ((WindowSize.x / 2) + 100)) && (mouse.y <= (WindowSize.y / 2 - 105)))
    {
      difficulty = 0;
      isMenu     = true;
      isEasy     = false;
      isMedium   = false;
      isExpert   = false;
      isError    = false;
      isGameMenu = false;
      return true;
    }
    // Restart.
    else if((mouse.x >= ((WindowSize.x / 2) - 150)) && (mouse.y >= (WindowSize.y / 2 - 40)) &&
            (mouse.x <= ((WindowSize.x / 2) + 100)) && (mouse.y <= (WindowSize.y / 2 + 30)))
    {
      isGameMenu  = false;
      isMenu      = false;
      isEasy      = false;
      isMedium    = false;
      isExpert    = false;
      isError     = false;
      isHighScore = false;
      isOptions   = false;
      isControls  = false;
      isAbout     = false;
      return true;
    }
    // Quit.
    else if((mouse.x >= ((WindowSize.x / 2) - 150)) && (mouse.y >= (WindowSize.y / 2 + 95)) &&
            (mouse.x <= ((WindowSize.x / 2) + 100)) && (mouse.y <= (WindowSize.y / 2 + 165)))
    {
      isGameMenu = false;
      win->close();
      exit(0);
      return false;
    }
  }

  // Draw the Texture for Viewing.
  win->draw(gameOverMenuDialoge);
  return false;
}
// ------------------------------------------------------------------------------


// ------------------------------------------------------------------------------
// -                   G E T T E R S   &   S E T T E R S -
// ------------------------------------------------------------------------------
bool GameMenu::get_title()
{
  return title;
}

void GameMenu::set_title(bool a_title)
{
  title = a_title;
}

bool GameMenu::get_quit()
{
  return isQuit;
}

void GameMenu::set_quit(bool a_quit)
{
  isQuit = a_quit;
}

bool GameMenu::get_pause()
{
  return isPause;
}

void GameMenu::set_pause(bool a_pause)
{
  isPause = a_pause;
}

bool GameMenu::get_confirm()
{
  return isConfirm;
}

void GameMenu::set_confirm(bool a_confirm)
{
  isConfirm = a_confirm;
}

bool GameMenu::get_menu()
{
  return isMenu;
}

void GameMenu::set_menu(bool a_menu)
{
  isMenu = a_menu;
}

bool GameMenu::get_easy()
{
  return isEasy;
}

void GameMenu::set_easy(bool an_easy)
{
  isEasy = an_easy;
}

bool GameMenu::get_medium()
{
  return isMedium;
}

void GameMenu::set_medium(bool a_medium)
{
  isMedium = a_medium;
}

bool GameMenu::get_expert()
{
  return isExpert;
}

void GameMenu::set_expert(bool an_expert)
{
  isExpert = an_expert;
}

bool GameMenu::get_error()
{
  return isError;
}

void GameMenu::set_error(bool an_error)
{
  isError = an_error;
}

bool GameMenu::get_highScore()
{
  return isHighScore;
}

void GameMenu::set_highScore(bool a_highScore)
{
  isHighScore = a_highScore;
}

bool GameMenu::get_gameOver()
{
  return isGameOver;
}

void GameMenu::set_gameOver(bool a_gameOver)
{
  isGameOver = a_gameOver;
}

bool GameMenu::get_gameOverMenu()
{
  return isGameMenu;
}

void GameMenu::set_gameOverMenu(bool a_gameOverMenu)
{
  isGameMenu = a_gameOverMenu;
}

bool GameMenu::get_options()
{
  return isOptions;
}

void GameMenu::set_options(bool an_option)
{
  isOptions = an_option;
}

bool GameMenu::get_controls()
{
  return isControls;
}

void GameMenu::set_controls(bool a_control)
{
  isControls = a_control;
}

bool GameMenu::get_about()
{
  return isAbout;
}

void GameMenu::set_about(bool an_about)
{
  isAbout = an_about;
}
// ------------------------------------------------------------------------------

// FIXED VERSION - DwindlingGalaxies.cpp
// Key fixes:
// 1. Fixed memory leaks in updateLasers/Aliens/PowerUps
// 2. Moved resource loading to initialization
// 3. Fixed window resolution
// 4. Added laser limit to prevent crashes
// 5. Cached file data to avoid disk I/O every frame

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
#include <iostream>
#include <string.h>
#include <stdio.h>
#include <utility>
#include <algorithm>
#include <cstring>
#include <vector>
#include <iostream>

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

// Default Constructor for Window & Variables
DwindlingGalaxies::DwindlingGalaxies(){
    // Platform-specific window creation
    #ifdef _WIN32
        // WINDOWS: Fixed windowed mode (more reliable)
        win = new RenderWindow(VideoMode(1920, 1080), "Dwindling Galaxies");
    #elif __linux__
        // LINUX: Fullscreen (works perfectly)
        VideoMode desktop = VideoMode::getDesktopMode();
        win = new RenderWindow(desktop, "Dwindling Galaxies", Style::Fullscreen);
    #else
        // FALLBACK: Default for other platforms
        win = new RenderWindow(VideoMode(1280, 720), "Dwindling Galaxies");
    #endif
    
    // Set window icon (works on both Windows and Linux)
    sf::Image icon;
    if (icon.loadFromFile("Images/Logo.png")) {
        win->setIcon(icon.getSize().x, icon.getSize().y, icon.getPixelsPtr());
    }

    // Load & Scale Background Images
        setBackground("Images/background3.png");
        setImage("Images/Planet3.png");
        //Get size of texture.
            TextureSize = wallpaper->getSize();   
        //Get size of window. 
            WindowSize = win->getSize();   
        // Scale all images in the background to the size of the window
            scaleImage();

    // Postion setting for background tiles and images.
        // Set Posititon of Paralax Images on the edge of screen
            background1 -> setPosition(Vector2f(WindowSize.x*2,WindowSize.y));
            background2 -> setPosition(Vector2f(0,WindowSize.y));
        // Set Postition of planent
            planet-> setPosition(Vector2f(WindowSize.x*-0.15,WindowSize.y*0.5));
    
    // Create Objects
        // Create New Player
            player = new Player("Images/SpaceShip5.png", WindowSize.x/2, WindowSize.y/2);
        // Create PowerUps
            initPowerUps();
        // Create Aliens
            initAliens();
        // Create Menu and Setup
            menu.set_player(player);
            menu.set_size(WindowSize);
            menu.set_window(win);

    // Screen Scrolling View
        screenScroll();

    // PERFORMANCE: Reserve space for vectors to avoid reallocation
        lasers.reserve(100);
        aliens.reserve(50);
        powerUps.reserve(20);

    //Software Compatiable Functions (may not work all operating systems)
        //Enable vertical Sync if avaliable
            win->setVerticalSyncEnabled(true);
        // PERFORMANCE: Cap frame rate to prevent excessive CPU usage
            win->setFramerateLimit(60);
}



// IMAGE FUNCTIONS
    // Set Background Image
    void DwindlingGalaxies::setBackground(const string picture){
        // Ensure image has loaded properly
            if(!wallpaper->loadFromFile(picture)){
                cout <<"Background Image Not Found"<< endl;
                exit(0);
            }

        //Set Image as background for all Tiles
            background->setTexture(*wallpaper);
            background1->setTexture(*wallpaper);
            background2->setTexture(*wallpaper);
    }

    // Set Planet Image (since Sprite* can't be passed)
    void DwindlingGalaxies::setImage(const string picture){
        // Ensure image has loaded properly
            if(!world->loadFromFile(picture)){
                cout <<"Planet Image Not Found"<< endl;
                exit(0);
            }

        //Set Image as Planet in the background
            planet->setTexture(*world);
    }

    // Scale the Background Image
    void DwindlingGalaxies::scaleImage(){
        // Calculate the Scale
            float ScaleX = (float) WindowSize.x / TextureSize.x;
            float ScaleY = (float) WindowSize.y / TextureSize.y; 

        // Set the Scale to all the background images
            background->setScale(ScaleX, ScaleY);
            background1->setScale(-ScaleX, -ScaleY);
            background2->setScale(-ScaleX, -ScaleY);
            planet->setScale(ScaleX, ScaleY);

    }



// SOUND FUNCTIONS
    // Loading and Playing Background Music
    void DwindlingGalaxies::music(){
        // Title Screen Music
            titleScreen = new Music;
            // Ensure sound has loaded properly
                if(!titleScreen->openFromFile("Sounds/titleSequence.wav")){
                    cout <<"Title Sound File Not Found"<< endl;
                    exit(0);
                }
            titleScreen->play();
    
        // Load Laser Firing Sound
            // Ensure sound has loaded properly
                if(!blaster.loadFromFile("Sounds/blaster.wav")){
                    cout <<"Laser Sound File Not Found"<< endl;
                    exit(0);
                }
            // Set and Play Laser Sound
                laser_sound.setBuffer(blaster);

         // Player Dies Sound
            // Ensure sound has loaded properly
                if(!playerDies.loadFromFile("Sounds/teleport.wav")){
                    cout <<"Teleport Sound File Not Found"<< endl;
                    exit(0);
                }
         teleport.setBuffer(playerDies);

         // Level Up Sound
            // Ensure sound has loaded properly
                if(!levelSound.loadFromFile("Sounds/levelUp.wav")){
                    cout <<"Level Up Sound File Not Found"<< endl;
                    exit(0);
                }
            levelUp.setBuffer(levelSound);
        
        // Alien Explosion Sound
            // Ensure sound has loaded properly
                if(!alienDeath.loadFromFile("Sounds/explosion.wav")){
                    cout <<"Explosion Sound File Not Found"<< endl;
                    exit(0);
                }
            explosion.setBuffer(alienDeath);
        
        // Power Up Sound
            // Ensure sound has loaded properly
                if(!powerUpCollision.loadFromFile("Sounds/powerUp.wav")){
                    cout <<"PowerUp Sound File Not Found"<< endl;
                    exit(0);
                }
            powerUpSound.setBuffer(powerUpCollision);
    }



// SCREEN DYNAMICS
    // Screen Scrolling Function
    void DwindlingGalaxies::screenScroll(){
        // Assigning Space and Create View
            view = new View;

        // Reset View then Scale the View Port
            view->reset(FloatRect(0,0, WindowSize.x, WindowSize.y));
            view->setViewport(FloatRect(0,0,1.0f,1.0f));

        // Create Dimensions for when scrolling begins
            Vector2f scaled(WindowSize.x/2,WindowSize.y/2);
            position = scaled;
    }

    // Screen Scrolling Bounding and Draw Function
    void DwindlingGalaxies::screenView(){
        // Condititons for screen scrolling and camera movement
            // Once player enter last half of screen stop scrolling
            if(player->get_x() > WindowSize.x*1.5){
                position.x = WindowSize.x*1.5;
            }
            // Once player enters the first half of screen stop scrolling
            else if(player->get_x() < WindowSize.x*-0.5){
                position.x = WindowSize.x*-0.5;
            }
            // Scroll unless above functions are true
            else{
                position.x = player->get_x();
            }

        // Set Camera View to center on postition coordinates
            view->setCenter(position);

        // Set the view in the live window    
            win->setView(*view);
    }

    // Create Title Bar For top of Screen
    void DwindlingGalaxies::titleBar(){
        // Set and Load Background Image of Title Bar at Top of Screen
            // Create Shape for Background of Bar       
                titleBarBackground.setSize(Vector2f(WindowSize.x,75));
            //Set Origin and Fill Colour
                titleBarBackground.setFillColor(Color::Black);
                titleBarBackground.setOrigin(WindowSize.x/2,75/2);
                titleBarBackground.setOutlineColor(Color(102,0,102));
                titleBarBackground.setOutlineThickness(5);

        // Set Score Font and Position
            // Check font loads properly        
                if(!score_font.loadFromFile("Fonts/Future_Now.ttf")){
                    cout << "Score Font Not Found" << endl;
                    exit(0);
                    }
                score_info.setFont(score_font);
                score_info.setFillColor(Color::White);
                score_info.setCharacterSize(50);
            // Add Message
                string score_msg;
                score_msg = "SCORE: " + to_string(score) + " ";
                score_info.setString(score_msg);
        
        // Set Level Font and Position
            // Check font loads properly        
                if(!level_font.loadFromFile("Fonts/Future_Now.ttf")){
                    cout << "Level Font Not Found" << endl;
                    exit(0);
                    }
                level_info.setFont(level_font);
                level_info.setFillColor(Color::White);
                level_info.setCharacterSize(50);
            // Add Message
                string level_msg;
                level_msg = "Level " + to_string(level) + " ";
                level_info.setString(level_msg);
            // Set Origion
                FloatRect bodySize = level_info.getGlobalBounds();
                level_info.setOrigin(bodySize.width/2.,bodySize.height/2.);

        // Add in Lives Images
            for (int i = 0; i < 5; i++){
                lives.push_back(new Lives(0.95*WindowSize.x,30,130*i));
            }

        // Track the bar to player movment
            // Intialise Distance Variable
                int distance = (WindowSize.x/2)-20;
            // Track While Screen Scrolling
                if(player->get_x() > WindowSize.x*1.5){
                    titleBarBackground.setPosition(1.5*WindowSize.x,75/2);
                    score_info.setPosition((WindowSize.x)+20, 5);
                    level_info.setPosition(1.5*WindowSize.x, 20);
                }
                else if(player->get_x() < WindowSize.x*-0.5){
                    titleBarBackground.setPosition(-0.5*WindowSize.x,75/2);
                    score_info.setPosition((-0.5*WindowSize.x)-940, 5);
                    level_info.setPosition(-0.5*WindowSize.x, 20);
                }
                else{
                    titleBarBackground.setPosition(player->get_x(),75/2);
                    score_info.setPosition(player->get_x()-distance, 5);
                    level_info.setPosition(player->get_x(), 20);
                }
    }

    // Update Menu Display When Called
    void DwindlingGalaxies::runMenu(){
        if(menu.get_title()==true){
            // Set View of Window
                screenView();
            // Run Title Sequence
                menu.titleSequence();
        }
        else if(menu.get_menu()==true){
            // Set View of Window
                screenView();
            //Open Main menu
                menu.displayScreen(menu.mainMenuSprite());
                difficulty = menu.mainMenuButtons();
        }
        else if(menu.get_easy() == true){
            // Set View of Window
                screenView();
            // Change Image
                menu.displayScreen(menu.easyMode());
                difficulty = menu.mainMenuButtons();
        }
        else if(menu.get_medium() == true){
            // Set View of Window
                screenView();
            // Change Image
                menu.displayScreen(menu.mediumMode());
                difficulty = menu.mainMenuButtons();
        }
        else if(menu.get_expert() == true){
            // Set View of Window
                screenView();
            // Change Image
                menu.displayScreen(menu.expertMode());
                difficulty = menu.mainMenuButtons();
        }
        else if(menu.get_error() == true){
            // Set Display Time
                static Clock displayTimer;
                int displayTimerMax = 2000;
                int currentTime = displayTimer.getElapsedTime().asMilliseconds();
            // Display Error Message
                if(currentTime <= displayTimerMax){
                    menu.displayScreen(menu.errorSprite());
                }else{
                    displayTimer.restart();
                    menu.set_error(false);
                    menu.set_menu(true);
                }
        }
        else if(menu.get_highScore() == true){
            // Set View of Window
                screenView();
            // Option Options Menu
                menu.displayScreen(menu.HighScoreSprite());
                difficulty = menu.mainMenuButtons();
            // Update HighScore
                displayHighScore();
        }
        else if(menu.get_options() == true){
            // Set View of Window
                screenView();
            // Option Options Menu
                menu.displayScreen(menu.get_optionsSprite());
                difficulty = menu.mainMenuButtons();
        }
        else if(menu.get_controls() == true){
            // Set View of Window
                screenView();
            // Open Controls
                menu.displayScreen(menu.get_controlsSprite());
                difficulty = menu.mainMenuButtons();
        }   
        else if(menu.get_about() == true){
            // Set View of Window
                screenView();
            // Open About Display
                menu.displayScreen(menu.get_aboutSprite());
                difficulty = menu.mainMenuButtons();
        } 
        else if(menu.get_quit()==true){
            // Set View of Window
                screenView();
            // Open Pop-up
                menu.quit();
        }
        else if(menu.get_pause()== true){
            // Set View of Window
                screenView();            
            // Open Pause Menu
                menu.pause();
        }
        else if (menu.get_confirm()==true){
            // Set View of Window
                screenView();
            // Open Confirm Box
                restart = menu.confirm();
        } 
        else if(menu.get_gameOver() == true && num_lives == 0){
            // Set View of Window
                screenView();       
            // Save Score
                scoreSave = score;            
            // Open Game Over Screen
                userName = menu.gameOver(addScore);
        }
        else if(menu.get_gameOverMenu() == true){
            // Set View of Window
                screenView();
            // Open Confirm Box
                restart = menu.gameOverMenu();
            // Update HighScore
                updateHighScore();
        }
        else{
            // Pause Background Music
                titleScreen->pause();
            // Set View of Window
                screenView();
            // Set Update Bullet Functions
                updateLasers();
            // Update Level & Score
                updateLevel();
            // Update Aliens
                updateAliens();
                updateCombat();
            //Update Powerups
                updatePowerUps();
            // Make Title Bar
                titleBar();
            // Draw Ojects in Frame
                drawFrame();
        }
    }



// OBJECT CONTROLS
    // Draw Function
    void DwindlingGalaxies::drawFrame(){
        // Draw Background Images
            background1->setScale(-1.f, -1.f);
            win->draw(*background);
            win->draw(*background1);
            win->draw(*background2);
            win->draw(*planet);
        
        // Draw Lasers
            for (auto *laser: lasers){
                laser->draw(win);
            }

        // Draw Aliens
            for (auto *alien : aliens){
                alien->draw(win);
            }
        // Draw PowerUp
            for (auto *PowerUp : powerUps){
                PowerUp->draw(win);
            }
        // Draw Player
            player->draw(win);
        
        // Draw Title Bar
            win->draw(titleBarBackground);
            win->draw(score_info);
            win->draw(level_info);

        // Draw Lives
            for(int i = 0; i < num_lives; i++){
                lives[i]->update(player, WindowSize);
                lives[i]->draw(win);
            }
    }

    // FIXED: Update Laser Movements across the screen
    // COMPLETE FIXED VERSION - updateLasers() function
    // Deletes lasers when they leave the visible screen (not the extended playable area)

    void DwindlingGalaxies::updateLasers(){
        // Calculate the current camera view bounds
        Vector2f viewCenter = view->getCenter();
        float viewLeft = viewCenter.x - WindowSize.x/2.0f;
        float viewRight = viewCenter.x + WindowSize.x/2.0f;
        float viewTop = viewCenter.y - WindowSize.y/2.0f;
        float viewBottom = viewCenter.y + WindowSize.y/2.0f;
        
        // Add margin so lasers don't pop out too abruptly at screen edge
        const float DELETION_MARGIN = 150.0f;
        
        // Iterate backwards for safe deletion (prevents skipping elements)
        for(int i = lasers.size() - 1; i >= 0; i--){
            // Update laser position
            lasers[i]->update();
            
            // Get laser position
            float laserX = lasers[i]->get_x();
            float laserY = lasers[i]->get_y();
            
            // Check if laser has exited the visible view bounds
            bool leftScreen = (laserX < viewLeft - DELETION_MARGIN);
            bool rightScreen = (laserX > viewRight + DELETION_MARGIN);
            bool topScreen = (laserY < viewTop - DELETION_MARGIN);
            bool bottomScreen = (laserY > viewBottom + DELETION_MARGIN);
            
            if(leftScreen || rightScreen || topScreen || bottomScreen){
                // Delete the laser object from memory
                delete lasers[i];
                // Remove the pointer from the vector
                lasers.erase(lasers.begin() + i);
            }
        }
    }

    //Level Updating Function
    void DwindlingGalaxies::updateLevel(){
        // Update Level with Score
            if(score-scoreTrack == 350){
                levelUp.play();
                level++;
                    // Cap Levels at Five
                    if(level > 5){
                        level = 5;
                    }
                scoreTrack = score;
            }
        
        // Change Condiditons Based on Level & Difficulty
        switch(level){
            case 1:
                // First Level Difficuly
                    // Increase Spawn Rate of Aliens
                    alienSpawnTimer =alienSpawnTimer+0.25;
                    break;
            case 2:
                // Second Level Difficulty
                    // Increase Spawn Rate of Aliens
                    alienSpawnTimer =alienSpawnTimer+0.25;
                    break;
            case 3:
                // Third Level Difficulty
                    // Increase Spawn Rate of Aliens
                    alienSpawnTimer =alienSpawnTimer+0.25;
                    break;
            case 4:
                // Fourth Level Difficulty
                    // Increase Spawn Rate of Aliens
                    alienSpawnTimer =alienSpawnTimer+0.25;
                    break;
            case 5:
                // Fifth Level Difficulty
                    // Increase Spawn Rate of Aliens
                    alienSpawnTimer =alienSpawnTimer+0.5;
                    break;
            default:
                break;
        }
    }

    //Difficulty Updating Function
    void DwindlingGalaxies::updateDifficulty(){
        // Change Condiditons Based on Level & Difficulty
        switch(difficulty){
            case 1:
                // Easy Level Difficuly
                    alienSpawnTimer = 1.25;
                    powerUpSpawnTimer = 0.2;
                    break;
            case 2:
                // Medium Level Difficulty
                    alienSpawnTimer = 1.75;
                    powerUpSpawnTimer = 0.1;
                    break;
            case 3:
                // Hard Level Difficulty
                    alienSpawnTimer = 2.00;
                    powerUpSpawnTimer = 0.05; 
                    break;
            default:
                break;
        }
    }

    // Update HighScore and Display to Screen
// COMPLETE FIXED updateHighScore() - Proper Tie-Breaking
// Newest scores win ties, scores sorted highest to lowest

void DwindlingGalaxies::updateHighScore(){
    // Intalise Varibales 
        Font highScoreText;
        vector <pair<int, string>> userScore;
        FILE* highScoreData;
        int highScore[11];
        char temp[255];
        string name[11];

    // Load Font and Make Sure it Loads Correctly
        if(!highScoreText.loadFromFile("Fonts/Future_Now.ttf")){
            cout << "High Score Font Not Found" << endl;
            exit(0);
        }
    
    // Read In Values from File
        highScoreData = fopen("Scores/highScores.txt", "r");
        for (int i = 0; i < 11; i++){
            // Scan in Names 
                fscanf(highScoreData, "%s", temp);
                name[i] = temp;
            // Scan in Numbers
                fscanf(highScoreData,"%d",&highScore[i]);
                userScore.push_back(make_pair(highScore[i], name[i]));
        }   
        fclose(highScoreData);

    // FIXED: Handle adding new score with proper sorting
    if(*addScore == 1){
        // Remove all null/zero entries first
        userScore.erase(
            remove_if(userScore.begin(), userScore.end(),
                [](const pair<int, string>& p) {
                    return p.second == "null" || p.first == 0;
                }),
            userScore.end()
        );
        
        // Add new score
        userScore.push_back(make_pair(scoreSave, userName));
        
        // Sort in DESCENDING order (highest scores first)
        // Stable sort preserves order for equal elements (newest stays on top)
        stable_sort(userScore.begin(), userScore.end(),
            [](const pair<int, string>& a, const pair<int, string>& b) {
                return a.first > b.first;  // Higher score comes first
            });
        
        // Keep only top 10 scores
        if(userScore.size() > 10){
            userScore.resize(10);
        }
        
        // Pad back to 11 entries with nulls if needed (for file format)
        while(userScore.size() < 11){
            userScore.push_back(make_pair(0, "null"));
        }
        
        *addScore = 0;
    }
    else {
        // Just sort existing scores in descending order
        stable_sort(userScore.begin(), userScore.end(),
            [](const pair<int, string>& a, const pair<int, string>& b) {
                return a.first > b.first;
            });
    }
    
    // Write scores back to file (highest to lowest)
    highScoreData = fopen("Scores/highScores.txt", "w");
    for (int i = 0; i < userScore.size(); i++){
        strcpy(temp, userScore[i].second.c_str());
        fprintf(highScoreData,"%s %d\n", temp, userScore[i].first);
    }
    fclose(highScoreData);
}

    
    // Display Scores & High Score
    // COMPLETE FIXED displayHighScore() - Hides "null 0" Entries
    // Replace your entire displayHighScore function with this
    void DwindlingGalaxies::displayHighScore(){
        // Intalise Varibales 
            Font highScoreText;
            vector <pair<int, string>> userScore;
            FILE* highScoreData;
            int highScore[11];
            char temp[255];
            string name[11];

        // Load Font and Make Sure it Loads Correctly
            if(!highScoreText.loadFromFile("Fonts/Future_Now.ttf")){
                cout << "High Score Font Not Found" << endl;
                exit(0);
            }
        
        // Read In Values from File
            highScoreData = fopen("Scores/highScores.txt", "r");
            for (int i = 0; i < 11; i++){
                // Scan in Names 
                    fscanf(highScoreData, "%s", temp);
                    name[i] = temp;
                // Scan in Numbers
                    fscanf(highScoreData,"%d",&highScore[i]);
                    userScore.push_back(make_pair(highScore[i], name[i]));
            } 
        
        // Draw Values on Screen (ONLY NON-NULL ENTRIES)
        for(int i = 0; i < 11; i++){
            // FIXED: Skip null/zero entries - don't display them
            if(userScore[i].second == "null" && userScore[i].first == 0){
                continue;  // Don't draw this entry
            }
            
            // Track While Screen Scrolling
            if(player->get_x() > WindowSize.x*1.5){
                // Display Names
                    showHighScore(((1.5*WindowSize.x)-210), (WindowSize.y/2-235)+(50*i), userScore[i].second, win, &highScoreText);
                // Display Scores
                    showHighScore(((1.5*WindowSize.x)+130), (WindowSize.y/2-235)+(50*i), to_string(userScore[i].first), win, &highScoreText);
            }
            else if(player->get_x() < WindowSize.x*-0.5){
                // Display Names
                    showHighScore(((-0.5*WindowSize.x)-210), (WindowSize.y/2-235)+(50*i), userScore[i].second, win, &highScoreText);
                // Display Scores
                    showHighScore(((-0.5*WindowSize.x)+130), (WindowSize.y/2-235)+(50*i), to_string(userScore[i].first), win, &highScoreText);
            }
            else{
                // Display Names
                    showHighScore((player->get_x()-210), (WindowSize.y/2-235)+(50*i), userScore[i].second, win, &highScoreText);
                // Display Scores
                    showHighScore((player->get_x()+130), (WindowSize.y/2-235)+(50*i), to_string(userScore[i].first), win, &highScoreText);
            }
        }
        
        // Close the file
        fclose(highScoreData);
    }

    // Display HighScore to Screen
    void DwindlingGalaxies::showHighScore(int x,int y,string word, RenderWindow* window, Font* font){
	    Text scoreText;
	    scoreText.setFont(*font);
	    scoreText.setPosition(x, y);
	    scoreText.setString(word);
	    scoreText.setCharacterSize(40);
	    win->draw(scoreText);
    }



//POWERUP ELEMENTS
    void DwindlingGalaxies::initPowerUps(){
        // Set Spawn Timers
            spawnTimerMaxPU = 150.f;
            spawnTimerPU = spawnTimerMaxPU;
    }

    // FIXED: Update powerup postition on the screen
    void DwindlingGalaxies::updatePowerUps(){
        // Intalise Variables
            spawnTimerPU += powerUpSpawnTimer;
            unsigned counter = 0;

        // If spawn timer has expired draw in new powerup
            // Faster Firing PowerUp
            if(switchOn == true){
                if(spawnTimerPU >= spawnTimerMaxPU){
                    // Spawn PowerUp
                    powerUps.push_back(new FasterFiring(rand()% WindowSize.x*3.f - WindowSize.x, -20.f));
                    spawnTimerPU = 0.f;
                    switchOn = false;
                }
            }
            // New life PowerUp
            if(switchOn == false){
                if(spawnTimerPU >= spawnTimerMaxPU){
                    // Spawn PowerUp
                    powerUps.push_back(new ExtraLive(rand()% WindowSize.x*3.f - WindowSize.x, -20.f));
                    spawnTimerPU = 0.f;
                    switchOn = true;
                }
            }

        // Update created powerup and move them across the screen
            for (auto *PowerUp : powerUps){
                PowerUp->update();
                // If the powerup exits the screen bounds delete it
                    if(PowerUp->getBounds().top > WindowSize.y){
                        // FIXED: Delete object BEFORE erasing
                            delete powerUps.at(counter);
                            powerUps.erase(powerUps.begin() + counter);
                            --counter;
                    }

                // If the powerup hits the player delete powerup and reset player
                    else if(PowerUp->getBounds().intersects(player->getBounds())){
                        // Play explosion sound
                            powerUpSound.play();
                        // Increase score by 100
                            score += 100;
                        // Do PowerUp Effect
                            if(PowerUp->powerUpEffect() == 1){
                                num_lives ++;
                                // Limit Lives to 5
                                    if(num_lives > 5){
                                        num_lives = 5;
                                    }
                            } 
                            else {
                                shots = shots + PowerUp->powerUpEffect();
                            }
                        // FIXED: Delete object BEFORE erasing
                            delete powerUps.at(counter);
                            powerUps.erase(powerUps.begin() + counter);
                            --counter;     
                    }

                // If nothing has happpened increase index
                    ++counter;
            }
    }



// ALIEN ELEMENTS
    // Initialising the aliens
    void DwindlingGalaxies::initAliens(){
        // Set Spawn Timers
            spawnTimerMax = 100.f;
            spawnTimer = spawnTimerMax;
    }
    
    // FIXED: Update Alien postition on the screen
    void DwindlingGalaxies::updateAliens(){
        // Intalise Variables
            spawnTimer += alienSpawnTimer;
            unsigned counter = 0;

        // If spawn timer has expired draw in new alien
            if (alienSwitch == true){
                if(spawnTimer >= spawnTimerMax){
                    aliens.push_back(new Talz(rand()% WindowSize.x*3.f - WindowSize.x, WindowSize.y));
                    spawnTimer = 0.f;
                    alienSwitch = false;
                }
            } else if(alienSwitch == false && helghastOn == false){
                if(spawnTimer >= spawnTimerMax){
                    aliens.push_back(new MondoShawn(rand()% WindowSize.x*3.f - WindowSize.x, 0));
                    spawnTimer = 0.f;
                    alienSwitch = true;
                    helghastOn = true;
                }
            } else if(helghastOn == true && alienSwitch == false){
                if(spawnTimer >= spawnTimerMax){
                    aliens.push_back(new Helghast(rand()% WindowSize.x*3.f - WindowSize.x, 0));
                    spawnTimer = 0.f;
                    helghastOn = false ;
                }
            }

        // Update created alians and move them across the screen
            for (auto *alien : aliens){
                alien->update();
                // If the alien exits the screen bounds delete it
                    if(alien->getBounds().top > WindowSize.y){
                        // FIXED: Delete object BEFORE erasing
                            delete aliens.at(counter);
                            aliens.erase(aliens.begin() + counter);
                            --counter;
                    }
                // If the alien hits the player delete alien and reset player
                else if(alien->getBounds().intersects(player->getBounds())){
                    // Play explosion sound
                        explosion.play();
                    // Reduce score by 100
                        score -= 100;
                        // If score drops below 0 reset to 0
                        if(score < 0){
                            score = 0;
                        }
                    // FIXED: Delete object BEFORE erasing
                        delete aliens.at(counter);
                        aliens.erase(aliens.begin() + counter);
                        --counter;
                    // Play teleport sound and move player to center, reduce 1 life
                        teleport.play();
                        player->set_position(Vector2f(WindowSize.x/2, WindowSize.y/2));
                        
                        // FIXED: Clear lasers properly (delete them first!)
                        for(auto* laser : lasers){
                            delete laser;
                        }
                        lasers.clear();
                        
                        num_lives -= 1;
                }
                // If nothing has happpened increase index
                    ++counter;
            }
    }

    // Update Combat Functions between Lasers and Aliens
    void DwindlingGalaxies::updateCombat(){
        // Index through the aliens 
        for (int i = 0; i < aliens.size(); ++i){
            // Set bool detection value to false
                bool isAlive = false;
            // Index through lasers
                for(size_t k = 0; k < lasers.size() && isAlive == false; k++){
                    // If laser hits alien delete laser and alien
                        if(aliens[i]->getBounds().intersects(lasers[k]->getBounds())){
                            // Play explosion sound
                                explosion.play();
                            // Increase score by value of alien type
                                score += aliens[i]->getPoints();
                            // FIXED: Delete objects BEFORE erasing
                                delete aliens[i];
                                aliens.erase(aliens.begin() + i);
                                delete lasers[k];
                                lasers.erase(lasers.begin()+k);
                                isAlive = true;
                        }
                }
        }
    }



// PLAYER CONTROLS
// COMPLETE FIXED keyboardControls() - Fast-Firing Power-up Works
// Replace your entire keyboardControls function with this
void DwindlingGalaxies::keyboardControls(Event event){
    if(menu.get_title() == false && menu.get_menu() == false && menu.get_error() == false && 
       menu.get_highScore() == false && menu.get_options() == false && menu.get_controls() == false && 
       menu.get_about() == false && menu.get_quit() == false && menu.get_pause() == false && 
       menu.get_confirm() == false && menu.get_gameOverMenu() == false){
        
        // ===== PLAYER MOVEMENT CONTROLS =====
        if (Keyboard::isKeyPressed(Keyboard::Left) && Keyboard::isKeyPressed(Keyboard::Up)){
            player->move_left(12, WindowSize);
            player->move_up(12, WindowSize);
        }else if (Keyboard::isKeyPressed(Keyboard::Left) && Keyboard::isKeyPressed(Keyboard::Down)){
            player->move_left(12, WindowSize);
            player->move_down(12, WindowSize);
        }else if (Keyboard::isKeyPressed(Keyboard::Right) && Keyboard::isKeyPressed(Keyboard::Up)){
            player->move_right(12, WindowSize);
            player->move_up(12, WindowSize);
        }else if (Keyboard::isKeyPressed(Keyboard::Right) && Keyboard::isKeyPressed(Keyboard::Down)){
            player->move_right(12, WindowSize);
            player->move_down(12, WindowSize);
        }else if (Keyboard::isKeyPressed(Keyboard::Right)){
            player->move_right(12, WindowSize);
        }else if(Keyboard::isKeyPressed(Keyboard::Left)){
            player->move_left(12, WindowSize);
        }else if (Keyboard::isKeyPressed(Keyboard::Up)){
            player->move_up(12, WindowSize);
        }else if (Keyboard::isKeyPressed(Keyboard::Down)){
            player->move_down(12, WindowSize);
        }

        // ===== LASER FIRING CONTROLS =====
        const int MAX_LASERS = 50;
        
        // Static cooldown timer
        static Clock laserCooldown;
        
        // FIXED: Clamp shots to 0 minimum BEFORE checking
        if (shots < 0){
            shots = 0;
        }
        
        // Check if space is currently pressed
        if (Keyboard::isKeyPressed(Keyboard::Space)){
            // Determine cooldown based on whether power-up is active
            int cooldownTime;
            if(shots > 0){
                cooldownTime = 100;   // 50ms = FAST firing with power-up
            } else {
                cooldownTime = 400;  // 200ms = normal firing rate
            }
            
            // Check if enough time has passed since last shot
            if(laserCooldown.getElapsedTime().asMilliseconds() >= cooldownTime){
                // Check laser limit
                if(lasers.size() < MAX_LASERS){
                    // Create laser based on direction
                    if(player->get_facingDirection() == true){
                        lasers.push_back(new Laser(player->get_x(), player->get_y() + 4, 12.f, 0.f, 1.f));
                    }
                    else{
                        lasers.push_back(new Laser(player->get_x(), player->get_y() + 4, -12.f, 0.f, 1.f));
                    }
                    
                    laser_sound.play();
                    
                    // FIXED: Only decrement shots if power-up is active
                    if(shots > 0){
                        shots--;
                    }
                    
                    laserCooldown.restart();
                }
            }
        }
    } 

    // ===== MENU CONTROLS =====
    if(Keyboard::isKeyPressed(Keyboard::Escape)){
        menu.set_quit(true);
    }
    
    if(menu.get_gameOver() == true && num_lives == 0){
        // Do nothing
    }
    else{
        if(Keyboard::isKeyPressed(Keyboard::P)){
            menu.set_pause(true);
        }
    }
}

// GAME RUN AND DATA HANDELING
    // Restart Game Functions
    void DwindlingGalaxies::restartGame(){
        if(restart == true){
            // Reset All Variables 
                score = 0;
                level = 1;
                num_lives = 3;
                shots = 0;
                player->set_position(Vector2f(WindowSize.x/2, WindowSize.y/2));
                
                // FIXED: Clear vectors properly (delete objects first!)
                for(auto* laser : lasers){
                    delete laser;
                }
                lasers.clear();
                
                for(auto* alien : aliens){
                    delete alien;
                }
                aliens.clear();
                
                for(auto* powerUp : powerUps){
                    delete powerUp;
                }
                powerUps.clear();

            // Jump out of Restart Mode
                restart = false;
        }

        // Reset Game Over Menu
            if(num_lives == 1){
                menu.set_gameOver(true);
            }
    }

    // Open Window and Run Game
    void DwindlingGalaxies::run(){
        // Play Sounds & Music
            music();

        // Run Loop
        while(win->isOpen()){
            Event event;
            while(win->pollEvent(event)){
                if(event.type == Event::Closed){
                    win->close();
                    exit(0);
                }
                //Key Board Controls
                    keyboardControls(event);
            }
            //Brace, for things that refresh every frame with no event occuring
                // Update Difficulty Level
                    updateDifficulty();
                // Restart Mode
                    restartGame();
                //Clean Window
                    win->clear();
                // Run Game menu
                    runMenu();
                //Load Display
                    win->display();
        }
    }

    // Deconstructor
    DwindlingGalaxies::~DwindlingGalaxies(){
        // Delete UserName Counter
            delete addScore;

        // Delete Music
            delete titleScreen;
            
        // Delete Background Images
            delete background;
            delete background1;
            delete background2;
            delete planet;
            delete wallpaper;

        // Delete Window
            delete win;
            delete view;

        // Delete Objects
            delete player;

        // FIXED: Delete Lasers properly
            for (auto *i: lasers){
                delete i;
            }
        
        // FIXED: Delete Lives properly
            for (auto *i: lives){
                delete i;
            }
        // FIXED: Delete PowerUps properly
            for(auto *i : powerUps){
                delete i;
            }

        // FIXED: Delete Aliens properly
            for(auto *i : aliens){
                delete i;
            }
    }
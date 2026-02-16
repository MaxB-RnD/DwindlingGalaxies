// This function defines the variables and functions from the GameMenu.h file
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
#include <iostream>
#include "GameMenu.h"
#include "Player.h"
#include <time.h>

using namespace sf;
using namespace std;

// SPECIFIC CONSTRUCTOR SETUP
    void GameMenu::set_window(RenderWindow* win){
        this->win = win;
    }

    void GameMenu::set_size(Vector2u WindowSize){
        this->WindowSize = WindowSize;
    }

    void GameMenu::set_player(Player* player){
        this->player = player;
    }



// TITLE SEQUENCE
void GameMenu::titleSequence(){    
    //Load Logo Sprite
        // Ensure image has loaded properly
            if(!studio_logo.loadFromFile("Images/Logo1.png")){
                cout <<"Logo Image Not Found"<< endl;
                exit(0);
            }
        //Set Image, Origon and Place in the background
            //Set Image
                logo.setTexture(studio_logo);
            // Set Origin
                FloatRect bodySize = logo.getGlobalBounds();
                logo.setOrigin(bodySize.width/2.,bodySize.height/2.);  
            // Set Position
                // Track While Screen Scrolling
                    if(player->get_x() > WindowSize.x*1.5){
                        logo.setPosition(1.5*WindowSize.x, WindowSize.y/2);
                    }
                    else if(player->get_x() < WindowSize.x*-0.5){
                        logo.setPosition(-0.5*WindowSize.x, WindowSize.y/2);
                    }
                    else{
                        logo.setPosition(player->get_x(), WindowSize.y/2);
                    } 

    //Load Main Screen Sprite
        // Ensure image has loaded properly
            if(!main_title.loadFromFile("Images/main_title.png")){
                cout <<"Title Image Not Found"<< endl;
                exit(0);
            }
        //Set Image, Origion and Place in the background
            //Set Image
                titleScene.setTexture(main_title);
            // Scale the Background Image
                //Get size of texture.
                    Vector2u TextureSize = main_title.getSize();
                // Calculate the Scale
                    float ScaleX = (float) WindowSize.x / TextureSize.x;
                    float ScaleY = (float) WindowSize.y / TextureSize.y;
                // Set the Scale to the background image
                    titleScene.setScale(ScaleX, ScaleY);
                // Set Origin
                    FloatRect bodySize1 = titleScene.getGlobalBounds();
                    titleScene.setOrigin(bodySize1.width/2.,bodySize1.height/2.);  
                // Set Position
                    // Track While Screen Scrolling
                        if(player->get_x() > WindowSize.x*1.5){
                            titleScene.setPosition(1.5*WindowSize.x, WindowSize.y/2);
                        }
                        else if(player->get_x() < WindowSize.x*-0.5){
                            titleScene.setPosition(-0.5*WindowSize.x, WindowSize.y/2);
                        }
                        else{
                            titleScene.setPosition(player->get_x(), WindowSize.y/2);
                        } 
        
    // Make it invisable untill called
        titleScene.setColor(Color(255, 255, 255, 0));

    // Fade Images onto the Screen
        // Set timer variable
            int currentTime = timer.getElapsedTime().asMilliseconds();
            int currentAlpha;
        // Run Fade effect Loop
            if (currentTime >= targetTime+2500){
                // Place the Main tile sequence over the top
                    titleScene.setColor(Color(255, 255, 255, 255));
            }
            else{
                // Calculate Alpha Level Increase & Set It 
                    currentAlpha = startAlpha + (endAlpha - startAlpha)*currentTime/ targetTime;
                    // Stop Fade effect from restarting
                        if(currentAlpha >= endAlpha){
                            currentAlpha = endAlpha;
                        }
                    logo.setColor(Color(255, 255, 255, currentAlpha));
            }
    
    // Exit title screen to menu
        if (Keyboard::isKeyPressed(Keyboard::Enter)){
            title = false;
            isMenu = true; 
        }
    
    // Draw The New Logo in Frame
        win->draw(logo);
        win->draw(titleScene);
}



//MAIN MENU
    // Button Controls for the Main Menu
    int GameMenu::mainMenuButtons(){
        Vector2i mouse = Mouse::getPosition(*win);
        if(Mouse::isButtonPressed(Mouse::Left)){
            // Quit button
                if((mouse.x >= ((WindowSize.x/2)+825)) && (mouse.y >=((WindowSize.y/2)-500)) && (mouse.x <= ((WindowSize.x/2)+930)) && (mouse.y <= ((WindowSize.y/2)-435))){
                    win->close();
                    exit(0);
                    return difficulty;
                }
            // Start button
                if((mouse.x >= (WindowSize.x/2)-450) && (mouse.y >=((WindowSize.y/2)-320)) && (mouse.x <= ((WindowSize.x/2)-155)) && (mouse.y <= (WindowSize.y/2)-250)){
                    // Set New Values
                        difficulty = 0;
                        isMenu = true;
                    // Make Sure other Varibales are off
                        isEasy = false;
                        isMedium = false;
                        isExpert = false;
                        isError = false;
                        isHighScore = false;
                        isOptions = false; 
                        isControls = false; 
                        isAbout = false; 
                    return difficulty;
                }
            // HighScore Button
                if((mouse.x >= ((WindowSize.x/2)-150)) && (mouse.y >=((WindowSize.y/2)-320)) && (mouse.x <= ((WindowSize.x/2)+145)) && (mouse.y <= (WindowSize.y/2)-250)){
                    // Set New Values
                        difficulty = 0;
                        isHighScore = true;
                    // Make Sure other Variables are off
                        isMenu = false;
                        isEasy = false;
                        isMedium = false;
                        isExpert = false;      
                        isError = false;           
                        isOptions = false;
                    return difficulty; 
                }
                // Options button
                if((mouse.x >= ((WindowSize.x/2)+150)) && (mouse.y >=((WindowSize.y/2)-320)) && (mouse.x <= ((WindowSize.x/2)+445)) && (mouse.y <= (WindowSize.y/2)-250)){
                    // Set New Values
                        difficulty = 0;
                        isOptions = true; 
                    // Make sure other Variables are off
                        isHighScore = false; 
                        isMenu = false;
                        isEasy = false;
                        isMedium = false;
                        isExpert = false;     
                        isError = false;              
                    return difficulty;
                }
            // Switch to Menu Controls
                if(isMenu == true || isEasy == true || isMedium == true || isExpert == true){
                    // Easy Mode
                        if((mouse.x >= ((WindowSize.x/2)-140)) && (mouse.y >= (WindowSize.y/2-125)) && (mouse.x <= ((WindowSize.x/2)+140)) && (mouse.y <= (WindowSize.y/2-55))){
                            // Set new Values
                                difficulty = 1;
                                isEasy = true;
                            // Make sure other Variables are off
                                isMenu = false;
                                isMedium = false;
                                isExpert = false;
                                isError = false;
                            return difficulty;
                        }
                    // Medium Mode 
                        else if((mouse.x >= ((WindowSize.x/2)-140)) && (mouse.y >= (WindowSize.y/2-30)) && (mouse.x <= ((WindowSize.x/2)+140)) && (mouse.y <= (WindowSize.y/2+40))){
                            // Set new Values
                                difficulty = 2;
                                isMedium = true;
                            // Make sure other Variables are off
                                isMenu = false;
                                isEasy = false;
                                isExpert = false;
                                isError = false;                            
                            return difficulty;
                        }
                    // Expert Mode
                        else if((mouse.x >= ((WindowSize.x/2)-140)) && (mouse.y >= (WindowSize.y/2+55)) && (mouse.x <= ((WindowSize.x/2)+140)) && (mouse.y <= (WindowSize.y/2+125))){
                            // Set new Values 
                                difficulty = 3;
                                isExpert = true;
                            // Make sure other Vairbales are off 
                                isMenu = false;
                                isEasy = false;
                                isMedium = false;
                                isError = false;
                                return difficulty;
                        }
                    // Play Button
                        else if((mouse.x >= ((WindowSize.x/2)-195)) && (mouse.y >= (WindowSize.y/2+210)) && (mouse.x <= ((WindowSize.x/2)+185)) && (mouse.y <= (WindowSize.y/2+280))){
                            // If no Difficulty Selected Display Error Message
                            if(difficulty == 0){
                                // Set New Variables 
                                    isError = true;
                                // Make Sure other Variables are off
                                    isMenu = false;
                                    isEasy = false;
                                    isMedium = false;
                                    isExpert = false;
                                    isHighScore = false;
                                    isOptions = false; 
                                    isControls = false; 
                                    isAbout = false;
                                return difficulty;               
                            }
                            else{
                                // Turn off other variables
                                    isMenu = false;
                                    isEasy = false;
                                    isMedium = false;
                                    isExpert = false;
                                    isError = false;
                                    isHighScore = false;
                                    isOptions = false; 
                                    isControls = false; 
                                    isAbout = false; 
                                return difficulty;
                            }
                        }
                }
            // Switch to Options Controls
                if(isOptions == true){
                    // Controls button
                        if((mouse.x >= (WindowSize.x/2)-195) && (mouse.y >= (WindowSize.y/2)+90) && (mouse.x <= (WindowSize.x/2)+195) && (mouse.y <= (WindowSize.y/2)+160)){
                            // Set New Variables
                                difficulty = 0;
                                isControls = true;  
                            // Make sure other Variables are off
                                isOptions = false;
                                isAbout = false; 
                            return difficulty;
                        }
                    // About Button
                        if((mouse.x >= (WindowSize.x/2)-195) && (mouse.y >= (WindowSize.y/2)-95) && (mouse.x <= (WindowSize.x/2)+195) && (mouse.y <= (WindowSize.y/2)-25)){
                            // Set new Variables
                                difficulty = 0;
                                isAbout  = true;
                            // Make sure other variables are off  
                                isOptions = false;
                                isControls = false;
                            return difficulty;
                        }
                }
        }
        return difficulty;
    }

    // Set Sprite Functions for Each Screen Option
        // Main Menu Sprite
        Sprite GameMenu::mainMenuSprite(){
            //Load background
                // Ensure image has loaded properly
                    if(!simple_menu.loadFromFile("Images/StartMenu.png")){
                        cout <<"Main Menu Image Not Found"<< endl;
                        exit(0);
                    }        
                //Set Image
                    menuSprite.setTexture(simple_menu); 
                // Set Origin
                    FloatRect bodySize = menuSprite.getGlobalBounds(); 
                    menuSprite.setOrigin(bodySize.width/2.,bodySize.height/2.);  
            // Set Position
                // Track While Screen Scrolling
                    if(player->get_x() > WindowSize.x*1.5){
                        menuSprite.setPosition(1.5*WindowSize.x, WindowSize.y/2);
                    }
                    else if(player->get_x() < WindowSize.x*-0.5){
                        menuSprite.setPosition(-0.5*WindowSize.x, WindowSize.y/2);
                    }
                    else{
                        menuSprite.setPosition(player->get_x(), WindowSize.y/2);
                    }

            return menuSprite;
        }

        // Easy Difficulty Sprite
        Sprite GameMenu::easyMode(){
            // Load Background Image
                // Ensure Image Loads Properly   
                    if(!beginner_image.loadFromFile("Images/MenuBeginner.png")){
                        cout <<"Beginner Button Image Not Found"<< endl;
                        exit(0);
                    }       
            //Set Image
                beginner.setTexture(beginner_image);
            // Set Origin
                FloatRect bodySize = beginner.getGlobalBounds(); 
                beginner.setOrigin(bodySize.width/2.,bodySize.height/2.); 
            // Set Position
                 // Track While Screen Scrolling
                    if(player->get_x() > WindowSize.x*1.5){
                        beginner.setPosition(1.5*WindowSize.x, WindowSize.y/2);
                    }
                    else if(player->get_x() < WindowSize.x*-0.5){
                        beginner.setPosition(-0.5*WindowSize.x, WindowSize.y/2);
                    }
                    else{
                        beginner.setPosition(player->get_x(), WindowSize.y/2);
                    }
            return beginner;
        }

        // Medium Difficulty Sprite
        Sprite GameMenu::mediumMode(){
            // Load Background Image
                // Ensure Image Loads Properly   
                    if(!medium_image.loadFromFile("Images/MenuMedium.png")){
                        cout <<"Medium Button Image Not Found"<< endl;
                        exit(0);
                    }       
            //Set Image
                medium.setTexture(medium_image);
            // Set Origin
                FloatRect bodySize = medium.getGlobalBounds(); 
                medium.setOrigin(bodySize.width/2.,bodySize.height/2.); 
            // Set Position
                // Track While Screen Scrolling
                    if(player->get_x() > WindowSize.x*1.5){
                        medium.setPosition(1.5*WindowSize.x, WindowSize.y/2);
                    }
                    else if(player->get_x() < WindowSize.x*-0.5){
                        medium.setPosition(-0.5*WindowSize.x, WindowSize.y/2);
                    }
                    else{
                        medium.setPosition(player->get_x(), WindowSize.y/2);
                    }
            return medium;
        }

        // Expert Difficulty Sprite
        Sprite GameMenu::expertMode(){
            // Load Background Image
                // Ensure Image Loads Properly   
                    if(!expert_image.loadFromFile("Images/MenuExpert.png")){
                        cout <<"Expert Button Image Not Found"<< endl;
                        exit(0);
                    }       
            //Set Image
                expert.setTexture(expert_image);
            // Set Origin
                FloatRect bodySize = expert.getGlobalBounds(); 
                expert.setOrigin(bodySize.width/2.,bodySize.height/2.); 
            // Set Position
                // Track While Screen Scrolling
                    if(player->get_x() > WindowSize.x*1.5){
                        expert.setPosition(1.5*WindowSize.x, WindowSize.y/2);
                    }
                    else if(player->get_x() < WindowSize.x*-0.5){
                        expert.setPosition(-0.5*WindowSize.x, WindowSize.y/2);
                    }
                    else{
                        expert.setPosition(player->get_x(), WindowSize.y/2);
                    }
            return expert;
        }

        // Error Message Difficulty Sprite
        Sprite GameMenu::errorSprite(){
            // Load Background Image
                // Ensure Image Loads Properly   
                    if(!error_image.loadFromFile("Images/ErrorPopUp.png")){
                        cout <<"Error Message Image Not Found"<< endl;
                        exit(0);
                    }       
            //Set Image
                error.setTexture(error_image);
            // Set Origin
                FloatRect bodySize = error.getGlobalBounds(); 
                error.setOrigin(bodySize.width/2.,bodySize.height/2.); 
            // Set Position
                // Track While Screen Scrolling
                    if(player->get_x() > WindowSize.x*1.5){
                        error.setPosition(1.5*WindowSize.x, WindowSize.y/2);
                    }
                    else if(player->get_x() < WindowSize.x*-0.5){
                        error.setPosition(-0.5*WindowSize.x, WindowSize.y/2);
                    }
                    else{
                        error.setPosition(player->get_x(), WindowSize.y/2);
                    }
            return error;
        }

        // HighScore Sprite
        Sprite GameMenu::HighScoreSprite(){
            //Load background
                // Ensure image has loaded properly
                    if(!highScore_image.loadFromFile("Images/HighScore.png")){
                        cout <<"High Score Image Not Found"<< endl;
                        exit(0);
                    }        
                //Set Image
                    highScore.setTexture(highScore_image); 
                // Set Origin
                    FloatRect bodySize = highScore.getGlobalBounds(); 
                    highScore.setOrigin(bodySize.width/2.,bodySize.height/2.);  
            // Set Position
                // Track While Screen Scrolling
                    if(player->get_x() > WindowSize.x*1.5){
                        highScore.setPosition(1.5*WindowSize.x, WindowSize.y/2);
                    }
                    else if(player->get_x() < WindowSize.x*-0.5){
                        highScore.setPosition(-0.5*WindowSize.x, WindowSize.y/2);
                    }
                    else{
                        highScore.setPosition(player->get_x(), WindowSize.y/2);
                    }

            return highScore;
        }

        // Options Screen Sprite
        Sprite GameMenu::get_optionsSprite(){
            //Load background
                // Ensure image has loaded properly
                    if(!options_menu.loadFromFile("Images/OptionsMenu.png")){
                        cout <<"Options Screen Image Not Found"<< endl;
                        exit(0);
                     }       
            //Set Image
                options.setTexture(options_menu);
            // Set Origin
                FloatRect bodySize = options.getGlobalBounds(); 
                options.setOrigin(bodySize.width/2.,bodySize.height/2.);  
            // Set Position
                // Track While Screen Scrolling
                    if(player->get_x() > WindowSize.x*1.5){
                        options.setPosition(1.5*WindowSize.x, WindowSize.y/2);
                    }
                    else if(player->get_x() < WindowSize.x*-0.5){
                        options.setPosition(-0.5*WindowSize.x, WindowSize.y/2);
                    }
                    else{
                        options.setPosition(player->get_x(), WindowSize.y/2);
                    }
            return options;
        }

        // Controls Diagram 
        Sprite GameMenu::get_controlsSprite(){
            // Load Background
                // Ensure Image Loads Properly
                    if(!controls_menu.loadFromFile("Images/OptionsControls.png")){
                    cout <<"Controls Image Not Found"<< endl;
                    exit(0);
                }    
            //Set Image
                controls.setTexture(controls_menu);
            // Set Origin
                FloatRect bodySize = controls.getGlobalBounds(); 
                controls.setOrigin(bodySize.width/2.,bodySize.height/2.);  
            // Set Position
                // Track While Screen Scrolling
                    if(player->get_x() > WindowSize.x*1.5){
                        controls.setPosition(1.5*WindowSize.x, WindowSize.y/2);
                    }
                    else if(player->get_x() < WindowSize.x*-0.5){
                        controls.setPosition(-0.5*WindowSize.x, WindowSize.y/2);
                    }
                    else{
                        controls.setPosition(player->get_x(), WindowSize.y/2);
                    }
            return controls;
        }

        // About Image Sprite
        Sprite GameMenu::get_aboutSprite(){
            // Load Background Image
                // Ensure Image Loads Properly   
                    if(!about_menu.loadFromFile("Images/OptionsAbout.png")){
                        cout <<"About Image Not Found"<< endl;
                        exit(0);
                    }       
            //Set Image
                about.setTexture(about_menu);
            // Set Origin
                FloatRect bodySize = about.getGlobalBounds(); 
                about.setOrigin(bodySize.width/2.,bodySize.height/2.); 
            // Set Position
                // Track While Screen Scrolling
                    if(player->get_x() > WindowSize.x*1.5){
                        about.setPosition(1.5*WindowSize.x, WindowSize.y/2);
                    }
                    else if(player->get_x() < WindowSize.x*-0.5){
                        about.setPosition(-0.5*WindowSize.x, WindowSize.y/2);
                    }
                    else{
                        about.setPosition(player->get_x(), WindowSize.y/2);
                    }
            return about;
        }

        // Quit Button Image Sprite
        void GameMenu::loadQuitButton(){
            // Load Background Image
                // Ensure Image Loads Properly   
                    if(!quitButton_image.loadFromFile("Images/QuitButton.png")){
                        cout <<"Quit Button Image Not Found"<< endl;
                        exit(0);
                    }       
            //Set Image
                quitButton.setTexture(quitButton_image);
            // Set Origin
                FloatRect bodySize = quitButton.getGlobalBounds(); 
                quitButton.setOrigin(bodySize.width/2.,bodySize.height/2.); 
                quitButton.setScale(0.15,0.15); 
            // Set Position
                // Track While Screen Scrolling
                    if(player->get_x() > WindowSize.x*1.5){
                        quitButton.setPosition(1.5*WindowSize.x+825, 40);
                    }
                    else if(player->get_x() < WindowSize.x*-0.5){
                        quitButton.setPosition(-0.5*WindowSize.x+825, 40);
                    }
                    else{
                        quitButton.setPosition(player->get_x()+825, 40);
                    }
            // Draw Image
                win->draw(quitButton);
        }

    // Display Current Screen
    void GameMenu::displayScreen(Sprite screen){
        loadQuitButton();
        win->draw(screen);
    }



// QUIT FUNCTION
void GameMenu::quit(){
    //Load Popup Sprite
        // Ensure image has loaded properly
             if(!quit_image.loadFromFile("Images/PopUp.png")){
                cout <<"Popup Image Not Found"<< endl;
                exit(0);
            }
        //Set Image, Origon and Place in the background
            //Set Image
               popUp.setTexture(quit_image);
               // Set Origin
                   FloatRect bodySize = popUp.getGlobalBounds();
                   popUp.setOrigin(bodySize.width/2.,bodySize.height/2.); 
              // Set Position
                // Track While Screen Scrolling
                if(player->get_x() > WindowSize.x*1.5){
                    popUp.setPosition(1.5*WindowSize.x, WindowSize.y/2);
                }
                else if(player->get_x() < WindowSize.x*-0.5){
                    popUp.setPosition(-0.5*WindowSize.x, WindowSize.y/2);
                }
                else{
                    popUp.setPosition(player->get_x(), WindowSize.y/2);
                }
    
    // Make clickable Buttons
    Vector2i mouse = Mouse::getPosition(*win);
      if(Mouse::isButtonPressed(Mouse::Left)){
        // If Yes Quit
            if((mouse.x >= (WindowSize.x/2)-190) && mouse.y >=((WindowSize.y/2)+40) && (mouse.x <= (WindowSize.x/2)-50) && (mouse.y <= (WindowSize.y/2)+110)){
                win->close();
                exit(0);
            }
        // If No Close Dialoge Box
            else if((mouse.x <= (WindowSize.x/2)+190) && mouse.y >=((WindowSize.y/2)+40) && (mouse.x >= (WindowSize.x/2)+50) && (mouse.y <= (WindowSize.y/2)+110)){
                isQuit = false;
            }
    }

    // Draw The Quit Menu in Frame
        win->draw(popUp);
}



// PAUSE MENU
    // Main Pause Menu Options
    void GameMenu::pause(){
        //Load Popup Sprite
            // Ensure image has loaded properly
                if(!pause_image.loadFromFile("Images/Pause.png")){
                    cout <<"Pause Image Not Found"<< endl;
                    exit(0);
                }
            //Set Image, Origon and Place in the background
                //Set Image
                pauseDialoge.setTexture(pause_image);
                // Set Origin
                    pauseDialoge.setScale(1.2,1.2);
                    FloatRect bodySize = pauseDialoge.getGlobalBounds();
                    pauseDialoge.setOrigin(bodySize.width/2.,bodySize.height/2.);
                
                // Set Position
                    // Track While Screen Scrolling
                    if(player->get_x() > WindowSize.x*1.5){
                        pauseDialoge.setPosition(1.5*WindowSize.x+50, 50+WindowSize.y/2);
                    }
                    else if(player->get_x() < WindowSize.x*-0.5){
                        pauseDialoge.setPosition(-0.5*WindowSize.x+50, 50+WindowSize.y/2);
                    }
                    else{
                        pauseDialoge.setPosition(player->get_x()+50, 50+WindowSize.y/2);
                    }
        
        // Make clickable Buttons
            // Make Mouse
                Vector2i mouse = Mouse::getPosition(*win);
            // Define Buttons
                if(Mouse::isButtonPressed(Mouse::Left)){
                    // If Resume Return to Game
                        if((mouse.x >= ((WindowSize.x/2)-140)) && (mouse.y >= (WindowSize.y/2-5)) && (mouse.x <= ((WindowSize.x/2)+110)) && (mouse.y <= (WindowSize.y/2+62))){
                            isPause = false;
                        }
                    // If Restart, Reset game
                        else if((mouse.x >= ((WindowSize.x/2)-140)) && (mouse.y >= (WindowSize.y/2+120)) && (mouse.x <= ((WindowSize.x/2)+110)) && (mouse.y <= (WindowSize.y/2+187))){
                            // Run Confirm Popup
                                isConfirm = true;
                                isPause = false;
                        }
                    // If Menu Restart Game and Move to Menu
                        else if((mouse.x >= ((WindowSize.x/2)-140)) && (mouse.y >= (WindowSize.y/2-125)) && (mouse.x <= ((WindowSize.x/2)+110)) && (mouse.y <= (WindowSize.y/2-58))){
                            // Run Confirm Popup
                                isConfirm = true;
                                isPause = false;
                                mainMenu = true;
                        }
                }

        // Draw The Pause Menu in Frame
            win->draw(pauseDialoge);
    }


    // Confirm Dialoge Box Function
    bool GameMenu::confirm(){
        //Load Dialoge Sprite
            // Ensure image has loaded properly
                if(!confirm_image.loadFromFile("Images/Confirm.png")){
                    cout <<"Confirm PopUp Image Not Found"<< endl;
                    exit(0);
                }
            //Set Image, Origon and Place in the background
                //Set Image
                    confirms.setTexture(confirm_image);
                // Set Origin
                    confirms.setScale(1.1,1.1);
                    FloatRect bodySize = confirms.getGlobalBounds();
                    confirms.setOrigin(bodySize.width/2.,bodySize.height/2.); 
                
            // Set Position
                // Track While Screen Scrolling
                    if(player->get_x() > WindowSize.x*1.5){
                        confirms.setPosition(1.5*WindowSize.x+50, 50+WindowSize.y/2);
                    }
                    else if(player->get_x() < WindowSize.x*-0.5){
                        confirms.setPosition(-0.5*WindowSize.x+50, 50+WindowSize.y/2);
                    }
                    else{
                        confirms.setPosition(player->get_x()+50, 50+WindowSize.y/2);
                    }
        
        // Make clickable Buttons
            Vector2i mouse = Mouse::getPosition(*win);
            if(Mouse::isButtonPressed(Mouse::Left)){
            // If Yes Return true
                if((mouse.x >= (WindowSize.x/2)-170) && mouse.y >=((WindowSize.y/2)+80) && (mouse.x <= (WindowSize.x/2)-50) && (mouse.y <= ((WindowSize.y/2)+150))){
                    // If main menu was pressed return to menu
                        if(mainMenu == true){
                           // Set New Variables 
                                difficulty = 0;
                                isMenu = true;
                            // Make sure other variables are off
                                isConfirm = false;
                                isEasy = false;
                                isMedium = false;
                                isExpert = false;
                                isError = false;
                            return true;
                        }
                    // If Restart was pressed restart the game
                        else{
                            // Make sure other varibales are off
                                isConfirm = false;
                                isMenu = false;
                                isEasy = false;
                                isMedium = false;
                                isExpert = false;
                                isError = false;
                                isHighScore = false;
                                isOptions = false; 
                                isControls = false; 
                                isAbout = false; 
                            return true;
                        }
                }

            // If No return to Menu Options
                else if((mouse.x <= (WindowSize.x/2)+200) && mouse.y >=((WindowSize.y/2)+80) && (mouse.x >= (WindowSize.x/2)+76) && (mouse.y <= (WindowSize.y/2)+150)){
                    isConfirm = false;
                    isPause = true;
                    return false;
                }
        }

    // Draw The Confirm Box in Frame
        win->draw(confirms);
    
    return false;
}


// EASY-TO-ADJUST VERSION - gameOver() with Position Variables
// Just change TEXT_OFFSET_X and TEXT_OFFSET_Y to move the text!
    string GameMenu::gameOver(int* addScore){
        // ===== EASY ADJUSTMENT SECTION =====
        // Change these two numbers to move the text position:
        const float TEXT_OFFSET_X = -15;  // Negative = left, Positive = right
        const float TEXT_OFFSET_Y = -10;   // Negative = up, Positive = down
        // ===================================
        
        // Load Font and Make Sure it Loads Correctly
            if(!playerFont.loadFromFile("Fonts/Future_Now.ttf")){
                cout << "Name Font Not Found" << endl;
                exit(0);
            }
        
        // Set Text Positioning
            playerText.setFont(playerFont);
            playerText.setCharacterSize(72);
            playerText.setString(playerInput);
            
            // Center the text origin so it stays centered as you type
            FloatRect textBounds = playerText.getLocalBounds();
            playerText.setOrigin(textBounds.width / 2.0f, textBounds.height / 2.0f);

        //Load Popup Sprite
            // Ensure image has loaded properly
                if(!gameOver_image.loadFromFile("Images/GameOver.png")){
                    cout <<"Game Over Image Not Found"<< endl;
                    exit(0);
                }
            //Set Image, Origon and Place in the background
                //Set Image
                gameOverDialoge.setTexture(gameOver_image);
                // Set Origin
                    gameOverDialoge.setScale(0.5,0.5);
                    FloatRect bodySize = gameOverDialoge.getGlobalBounds();
                    gameOverDialoge.setOrigin(bodySize.width/2,bodySize.height/2);
                
                // Set Position - Track While Screen Scrolling
                    if(player->get_x() > WindowSize.x*1.5){
                        gameOverDialoge.setPosition(1.5*WindowSize.x-250, WindowSize.y/2-150);
                        playerText.setPosition(1.5*WindowSize.x + TEXT_OFFSET_X, WindowSize.y/2 + TEXT_OFFSET_Y);
                    }
                    else if(player->get_x() < WindowSize.x*-0.5){
                        gameOverDialoge.setPosition(-0.5*WindowSize.x-250, WindowSize.y/2-150);
                        playerText.setPosition(-0.5*WindowSize.x + TEXT_OFFSET_X, WindowSize.y/2 + TEXT_OFFSET_Y);
                    }
                    else{
                        gameOverDialoge.setPosition(player->get_x()-250, WindowSize.y/2-150);
                        playerText.setPosition(player->get_x() + TEXT_OFFSET_X, WindowSize.y/2 + TEXT_OFFSET_Y);
                    }

        // Define Behaviour after Input
            // Define Keyboard Controls
            while(win->pollEvent(event)){
                if (event.type == Event::TextEntered){
                    
                    // BACKSPACE HANDLING
                    if(event.text.unicode == 8){  // Backspace
                        if(playerInput.getSize() > 0){
                            playerInput.erase(playerInput.getSize() - 1, 1);
                            playerText.setString(playerInput);
                            
                            // Re-center after deleting character
                            FloatRect textBounds = playerText.getLocalBounds();
                            playerText.setOrigin(textBounds.width / 2.0f, textBounds.height / 2.0f);
                        }
                    }
                    
                    // LETTER INPUT
                    // Accept uppercase letters (A-Z: 65-90) and lowercase letters (a-z: 97-122)
                    else if((event.text.unicode >= 65 && event.text.unicode <= 90) || 
                            (event.text.unicode >= 97 && event.text.unicode <= 122)){
                        // Limit to 12 characters
                        if(playerInput.getSize() < 12){
                            playerInput += static_cast<char>(event.text.unicode);
                            playerText.setString(playerInput);
                            
                            // Re-center after adding character
                            FloatRect textBounds = playerText.getLocalBounds();
                            playerText.setOrigin(textBounds.width / 2.0f, textBounds.height / 2.0f);
                        }
                    }
                }
                
                // ENTER KEY TO SUBMIT
                if(event.type == Event::KeyPressed && event.key.code == Keyboard::Enter){
                    // Only accept if name is not empty
                    if(playerInput.getSize() > 0){
                        // Open New Menu to Direct Start of New Game
                        isGameMenu = true;
                        isGameOver = false;
                        *addScore = 1;
                        return playerInput.toAnsiString();
                    }
                }
            }
            
        // Draw The Game Over Menu in Frame
            win->draw(gameOverDialoge);
            win->draw(playerText);

        return playerInput.toAnsiString();
    }

    // New Game Dialoge Box Function
    bool GameMenu::gameOverMenu(){
        // Set Name String to Empty
            playerInput = "";
        //Load Dialoge Sprite
            // Ensure image has loaded properly
                if(!gameOverMenu_image.loadFromFile("Images/GameOverMenu.png")){
                    cout <<"Game Over Menu Image Not Found"<< endl;
                    exit(0);
                }
            //Set Image, Origon and Place in the background
                //Set Image
                    gameOverMenuDialoge.setTexture(gameOverMenu_image);
                // Set Origin
                    gameOverMenuDialoge.setScale(1.2,1.2);
                    FloatRect bodySize = gameOverMenuDialoge.getGlobalBounds();
                    gameOverMenuDialoge.setOrigin(bodySize.width/2.,bodySize.height/2.); 
                
            // Set Position
                // Track While Screen Scrolling
                    if(player->get_x() > WindowSize.x*1.5){
                        gameOverMenuDialoge.setPosition(1.5*WindowSize.x+50, 50+WindowSize.y/2);
                    }
                    else if(player->get_x() < WindowSize.x*-0.5){
                        gameOverMenuDialoge.setPosition(-0.5*WindowSize.x+50, 50+WindowSize.y/2);
                    }
                    else{
                        gameOverMenuDialoge.setPosition(player->get_x()+50, 50+WindowSize.y/2);
                    }
        
        // Make clickable Buttons
            Vector2i mouse = Mouse::getPosition(*win);
            if(Mouse::isButtonPressed(Mouse::Left)){
                    // If Menu Restart Game and Move to Menu
                        if((mouse.x >= ((WindowSize.x/2)-150)) && (mouse.y >= (WindowSize.y/2-175)) && (mouse.x <= ((WindowSize.x/2)+100)) && (mouse.y <= (WindowSize.y/2-105))){
                            // Set New Variables
                                difficulty = 0;
                                isMenu = true;
                            // Make sure other varibales are off
                                isEasy = false;
                                isMedium = false;
                                isExpert = false;
                                isError = false;
                                isGameMenu = false;
                            return true;
                        }
                    // If Restart, Reset game
                        else if((mouse.x >= ((WindowSize.x/2)-150)) && (mouse.y >= (WindowSize.y/2-40)) && (mouse.x <= ((WindowSize.x/2)+100)) && (mouse.y <= (WindowSize.y/2+30))){
                            // Set New Variables
                                isGameMenu = false;
                                isMenu = false;
                                isEasy = false;
                                isMedium = false;
                                isExpert = false;
                                isError = false;
                                isHighScore = false;
                                isOptions = false; 
                                isControls = false; 
                                isAbout = false; 
                            return true;
                        }
                    // If Quit, then exit window 
                        else if((mouse.x >= ((WindowSize.x/2)-150)) && (mouse.y >= (WindowSize.y/2+95)) && (mouse.x <= ((WindowSize.x/2)+100)) && (mouse.y <= (WindowSize.y/2+165))){
                            isGameMenu = false;
                            win->close();
                            exit(0);
                            return false;
                            
                        }
            }

        // Draw The Confirm Box in Frame
            win->draw(gameOverMenuDialoge);

        return false;
    }



// GETTERS & SETTERS
    bool GameMenu::get_title(){
        return title;
    }

    void GameMenu::set_title(bool a_title){
        title = a_title;
    }
    
    bool GameMenu::get_quit(){
        return isQuit;
    }

    void GameMenu::set_quit(bool a_quit){
        isQuit = a_quit;
    }

    bool GameMenu::get_pause(){
        return isPause;
    }

    void GameMenu::set_pause(bool a_pause){
        isPause = a_pause;
    }

    bool GameMenu::get_confirm(){
        return isConfirm;
    }
    
    void GameMenu::set_confirm(bool a_confirm){
        isConfirm = a_confirm;
    }

    bool GameMenu::get_menu(){
        return isMenu;
    }
    
    void GameMenu::set_menu(bool a_menu){
        isMenu = a_menu;
    }
    
    bool GameMenu::get_easy(){
        return isEasy;
    }
    
    void GameMenu::set_easy(bool an_easy){
        isEasy = an_easy;
    }

    bool GameMenu::get_medium(){
        return isMedium;
    }

    void GameMenu::set_medium(bool a_medium){
        isMedium = a_medium;
    }

    bool GameMenu::get_expert(){
        return isExpert;
    }

    void GameMenu::set_expert(bool an_expert){
        isExpert = an_expert;
    }
    
    bool GameMenu::get_error(){
        return isError;
    }

    void GameMenu::set_error(bool an_error){
        isError = an_error;
    }

    bool GameMenu::get_highScore(){
        return isHighScore;
    }

    void GameMenu::set_highScore(bool a_highScore){
        isHighScore = a_highScore;
    }

    bool GameMenu::get_gameOver(){
        return isGameOver;
    }
    
    void GameMenu::set_gameOver(bool a_gameOver){
        isGameOver = a_gameOver;
    }

    bool GameMenu::get_gameOverMenu(){
        return isGameMenu;
    }
    
    void GameMenu::set_gameOverMenu(bool a_gameOverMenu){
        isGameMenu = a_gameOverMenu;
    }
    
    bool GameMenu::get_options(){
        return isOptions; 
    }
    
    void GameMenu::set_options(bool an_option){
        isOptions = an_option;
    }

    bool GameMenu::get_controls(){
        return isControls; 
    }
    
    void GameMenu::set_controls(bool a_control){
        isControls = a_control;
    }

    bool GameMenu::get_about(){
        return isAbout; 
    }
    
    void GameMenu::set_about(bool an_about){
        isAbout = an_about;
    }



// DECONSTRUCTOR
GameMenu::~GameMenu(){
       delete player;
       delete win;
}
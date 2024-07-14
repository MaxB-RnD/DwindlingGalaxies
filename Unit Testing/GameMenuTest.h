// this file will test functions unique to GameMenu
#include <iostream>
#include "GameMenu.h"

class GameMenuTest {
public:
    void runTests() {
     testIsConfirm();
	   testTitle();
	   testIsQuit();
	   testIsPause();
	   testIsMenu();
    }
private:
        

 void testIsConfirm() {
        // Create an instance of GameMenu
        GameMenu menu;
        // Set up the initial state for the test
       menu.set_confirm(true);
        //Get the value of isConfirm
        bool isConfirm = menu.get_confirm();
        // Check if isConfirm is true
        if (isConfirm) {
           std::cout << "testIsConfirm() passed!" << std::endl;
        } else {
            std::cout << "testIsConfirm() failed!" << std::endl;
        }
    }

void testTitle() {
        // Create an instance of GameMenu
        GameMenu menu;
        // Set up the initial state for the test
        menu.set_title(true);
        // Get the value of title
        bool title = menu.get_title();
        // Check if title is true
        if (title) {
            std::cout << "testTitle() passed!" << std::endl;
        } else {
            std::cout << "testTitle() failed!" << std::endl;
        }
    }



void testIsQuit() {
        // Create an instance of GameMenu
        GameMenu menu;
        // Set up the initial state for the test
        menu.set_quit(true);
        // Get the value of isQuit
        bool isQuit = menu.get_quit();
        // Check if isQuit is true
        if (isQuit) {
            std::cout << "testIsQuit() passed!" << std::endl;
        } else {
            std::cout << "testIsQuit() failed!" << std::endl;
        }
    }


void testIsPause() {
        // Create an instance of GameMenu
        GameMenu menu;
        // Set up the initial state for the test
        menu.set_pause(true);
        // Get the value of isPause
        bool isPause = menu.get_pause();
        // Check if isPause is true
        if (isPause) {
            std::cout << "testIsPause() passed!" << std::endl;
        } else {
            std::cout << "testIsPause() failed!" << std::endl;
        }
    }

void testIsMenu() {
        // Create an instance of GameMenu
        GameMenu menu;
        // Set up the initial state for the test
        menu.set_menu(true);
        // Get the value of isMenu
        bool isMenu = menu.get_menu();
        // Check if isMenu is true
        if (isMenu) {
            std::cout << "testIsMenu() passed!" << std::endl;
        } else {
            std::cout << "testIsMenu() failed!" << std::endl;
        }
    }

};

#include "Game.h"
#include <iostream>



Game::Game() {
    std::cout << "Fadi and his friends!" << std::endl;
    setupMaps();
    GameStarter();
}

void Game::GameStarter() {
    bool preGameSetupComplete = true;
    
    while (preGameSetupComplete) {
        std::cout << "Enter your name: ";
        std::cin >> playerName;

        if (playerName.empty()) {
            std::cout << "Name cannot be empty. Please try again." << std::endl;
        } else {
            preGameSetupComplete = false;

            std::cout << "Welcome, " << playerName << "! Let's start the game." << std::endl;
            GameOn();
        }
    }

}


void Game::GameOn() {
    while (gameRunning) {
        std::cout << "Current Chapter: " << currentChapter << std::endl;
        std::cout << "Lives: " << lives << std::endl;
        std::cout << "Energy: " << energy << std::endl;

        // Display available actions
        std::cout << "Available Actions:" << std::endl;


        for (const auto& action : maps[currentChapter - 1].actions) 
        {
            std::cout << "- " << action << std::endl;
        }

        // Get user input for action
        std::string userAction;
        std::cout << "Choose an action: ";
        std::cin >> userAction;

        // Process the action (this is a placeholder, actual logic will depend on the game design)
        if (userAction == "exit") 
        {
            std::cout << "Exiting the game. Goodbye!" << std::endl;
            gameRunning = false;
            break;
        }
        
        else
        {
            std::cout << "You chose to: " << userAction << std::endl;
            // Update game state based on action
            // For example, change chapter, reduce lives, etc.
        }


    }
}



void Game::setupMaps() {
    // Example setup for maps
    Map map1;
    map1.id = 1;
    map1.name = "Chapter 1: The Beginning";
    map1.description = "This is the first chapter of the game.";
    map1.characters = {"Fadi", "Friend1", "Friend2"};
    map1.actions = {"explore", "talk", "exit"};
    map1.connectedMaps = {2};

    Map map2;
    map2.id = 2;
    map2.name = "Chapter 2: The Adventure Continues";
    map2.description = "This is the second chapter of the game.";
    map2.characters = {"Fadi", "Friend3"};
    map2.actions = {"explore", "fight", "exit"};
    map2.connectedMaps = {1};

    maps.push_back(map1);
    maps.push_back(map2);

    // Initialize game state
    currentChapter = 1;
    lives = 3;
    energy = 100;
}
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
        Room* currentRoomData = getCurrentRoom();

        if (currentRoomData == nullptr) {
            std::cout << "Could not find the current room." << std::endl;
            gameRunning = false;
            break;
        }

        std::cout << "Current Chapter: " << currentChapter << std::endl;
        std::cout << "Current Room: [" << currentRoomData->id << "] "
                  << currentRoomData->name << std::endl;
        std::cout << currentRoomData->description << std::endl;
        std::cout << "Lives: " << lives << std::endl;
        std::cout << "Energy: " << energy << std::endl;

        showConnectedRooms(*currentRoomData);

        std::cout << "\nCommands: rooms, move, quit" << std::endl;
        std::cout << "Room actions: ";
        for (const auto& action : currentRoomData->actions) {
            std::cout << action << " ";
        }
        std::cout << std::endl;

        std::string userAction;
        std::cout << "\nChoose an action: ";
        if (!(std::cin >> userAction)) {
            gameRunning = false;
            break;
        }

        if (userAction == "quit" || userAction == "exit") {
            std::cout << "Exiting the game. Goodbye!" << std::endl;
            gameRunning = false;
        } else if (userAction == "rooms" || userAction == "explore") {
            showConnectedRooms(*currentRoomData);
        } else if (userAction == "move") {
            int roomId;
            std::cout << "Enter the room ID you want to move to: ";
            if (std::cin >> roomId) {
                moveToRoom(roomId);
            } else {
                std::cout << "Please enter a valid room ID." << std::endl;
                std::cin.clear();
                std::cin.ignore(10000, '\n');
            }
        } else {
            bool actionExists = false;
            for (const auto& action : currentRoomData->actions) {
                if (action == userAction) {
                    actionExists = true;
                    break;
                }
            }

            if (actionExists) {
                std::cout << "The action '" << userAction
                          << "' is not implemented yet." << std::endl;
            } else {
                std::cout << "That command is not available here." << std::endl;
            }
        }
    }
}


Room* Game::findRoom(int roomId) {
    if (currentChapter < 1 || currentChapter > static_cast<int>(maps.size())) {
        return nullptr;
    }

    for (auto& room : maps[currentChapter - 1].rooms) {
        if (room.id == roomId) {
            return &room;
        }
    }

    return nullptr;
}


Room* Game::getCurrentRoom() {
    return findRoom(currentRoom);
}


void Game::showConnectedRooms(const Room& room) {
    std::cout << "\nAvailable rooms:" << std::endl;

    if (room.connectedRooms.empty()) {
        std::cout << "- There are no connected rooms." << std::endl;
        return;
    }

    for (const int roomId : room.connectedRooms) {
        Room* connectedRoom = findRoom(roomId);
        if (connectedRoom == nullptr) {
            continue;
        }

        std::cout << "- [" << connectedRoom->id << "] "
                  << connectedRoom->name;
        if (connectedRoom->locked) {
            std::cout << " (LOCKED";
            if (!connectedRoom->lockReason.empty()) {
                std::cout << ": " << connectedRoom->lockReason;
            }
            std::cout << ")";
        } else {
            std::cout << " (available)";
        }
        std::cout << std::endl;
    }
}


void Game::moveToRoom(int roomId) {
    Room* currentRoomData = getCurrentRoom();
    Room* targetRoom = findRoom(roomId);

    if (currentRoomData == nullptr || targetRoom == nullptr) {
        std::cout << "That room does not exist." << std::endl;
        return;
    }

    bool isConnected = false;
    for (const int connectedRoomId : currentRoomData->connectedRooms) {
        if (connectedRoomId == roomId) {
            isConnected = true;
            break;
        }
    }

    if (!isConnected) {
        std::cout << "That room is not connected to the current room." << std::endl;
        return;
    }

    if (targetRoom->locked) {
        std::cout << "That room is locked";
        if (!targetRoom->lockReason.empty()) {
            std::cout << ": " << targetRoom->lockReason;
        }
        std::cout << "." << std::endl;
        return;
    }

    currentRoom = targetRoom->id;
    std::cout << "You moved to " << targetRoom->name << "." << std::endl;
}


void Game::setupMaps(){
    // Example setup for maps

    Map map1;
    map1.id = 1;
    map1.name = "OutSide";
    map1.description = "This is the first chapter of the game.";
    map1.characters = {"Fadi", "Friend1", "Friend2"};
    map1.actions = {"explore", "talk", "exit"};
    map1.connectedMaps = {2};
    
    Room room1;
    room1.id = 1;
    room1.name = "Room 1";
    room1.description = "This is the first room in the first map.";
    room1.characters = {"Fadi", "Friend1"};
    room1.actions = {"explore", "fight", "exit"};
    room1.connectedRooms = {2};

    map1.rooms.push_back(room1);

    Room room2;
    room2.id = 2;
    room2.name = "Room 2";
    room2.description = "This is the second room in the first map.";
    room2.characters = {"Fadi", "Friend2"};
    room2.actions = {"explore", "fight", "exit"};
    room2.connectedRooms = {1};

    map1.rooms.push_back(room2);


    Map map2;
    map2.id = 2;
    map2.name = "Malmö university first floor";
    map2.description = "This is the second chapter of the game.";
    map2.characters = {"Fadi", "Friend3"};
    map2.actions = {"explore", "fight", "exit"};
    map2.connectedMaps = {3};

    Map map3;
    map3.id = 3;
    map3.name = "Malmö university second floor";
    map3.description = "This is the third chapter of the game.";
    map3.characters = {"Fadi", "Friend4"};
    map3.actions = {"explore", "exit"};
    map3.connectedMaps = {4};

    Map map4;
    map4.id = 4;
    map4.name = "Malmö C subway";
    map4.description = "This is the fourth chapter of the game.";
    map4.characters = {"Fadi", "Friend4"};
    map4.actions = {"explore", "exit"};
    map4.connectedMaps = {0};




    maps.push_back(map1);
    maps.push_back(map2);
    maps.push_back(map3);
    maps.push_back(map4);

    // Initialize game state
    currentChapter = 1;
    lives = 3;
    energy = 100;
}
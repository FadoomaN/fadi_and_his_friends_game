#pragma once
#include <string>
#include <vector>
#include "Map.h"
#include "Room.h"


class Game {


private:

    //Gaame attributes
    std::string playerName;
    int lives = 0;
    int totalChapters = 0;
    int currentChapter = 1;
    int currentRoom = 1;
    int energy = 0;
    std::vector<Map> maps;
    bool gameRunning = true;
    
    
    //Game functions
    void GameStarter();
    void GameOn();
    void setupMaps();
    Room* findRoom(int roomId);
    Room* getCurrentRoom();
    void showConnectedRooms(const Room& room);
    void moveToRoom(int roomId);
    


public:
    Game();
    
};
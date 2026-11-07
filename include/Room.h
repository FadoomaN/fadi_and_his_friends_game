#pragma once


#include <string>
#include <vector>

struct Room {
    int id;
    std::string name;
    std::string description;
    bool locked = false;
    std::string lockReason;

    std::vector<std::string> characters;
    std::vector<std::string> actions;
    std::vector<int> connectedRooms;
};
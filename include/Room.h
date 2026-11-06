#pragma once


#include <string>
#include <vector>

struct Room {
    int id;
    std::string name;
    std::string description;

    std::vector<std::string> characters;
    std::vector<std::string> actions;
    std::vector<int> connectedRooms;
};
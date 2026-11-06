#pragma once

#include <string>
#include <vector>
#include "Room.h"

struct Map {
    std::string name;
    std::string description;

    std::vector<std::string> characters;
    std::vector<std::string> actions;
    std::vector<int> connectedMaps;
    std::vector<Room> rooms;
};
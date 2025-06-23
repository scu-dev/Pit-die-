#pragma once
#include <vector>

#include "Room.hpp"

using std::vector;

class Game {
private:
    vector<vector<Room*>> rooms;
    const int size_;

public:
    Game(int size) noexcept : size_(size) {

    }
    void run() noexcept {

    }
};
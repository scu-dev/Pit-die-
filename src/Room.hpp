#pragma once

#include "Player.hpp"
#include "Gold.hpp"
#include "Pit.hpp"
#include "Event.hpp"

class Room {
    Player* player_;
    Event* event_;
public:
    Room() noexcept : player_(nullptr), event_(nullptr) {}
    Room(Player* player) noexcept : player_(player), event_(nullptr) {}
    void show() noexcept {
        if (player_ == nullptr) cout << " ";
        else cout << "*";
    }
    static Room* roomWithPlayer(Player* player) noexcept {
        auto* result = new Room(player);
        return result;
    }
    static Room* roomWithGold() noexcept {
        auto* result = new Room();
        result->event_ = new Gold();
        return result;
    }
    static Room* roomWithPit() noexcept {
        auto* result = new Room();
        result->event_ = new Pit();
        return result;
    }
    static Room* roomWithEmpty() noexcept {
        auto* result = new Room();
        return result;
    }
};
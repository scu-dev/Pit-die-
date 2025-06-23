#pragma once
#include <iostream>

#include "Player.hpp"
#include "Gold.hpp"
#include "Pit.hpp"
#include "Event.hpp"

using std::cout, std::endl;

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
    void enter(Player* player) {
        player_ = player;
        if (event_ != nullptr && event_->die()) throw std::runtime_error("你 die 了！");
    }
    bool hasReward() const noexcept {
        if (event_ == nullptr) return false;
        else return event_->reward();
    }
    void leave() noexcept {
        player_ = nullptr;
    }
    void percept() noexcept {
        if (event_ != nullptr) event_->percept();
        else cout << "你感觉湿漉漉的！" << endl;
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
#pragma once
#include <iostream>

#include "Event.hpp"

class Pit : public Event {
    void percept() const noexcept override {
        std::cout << "你感到一阵冷飕飕的阴风！" << std::endl;
    }
    bool die() const noexcept override {
        return true;
    }
};
#pragma once
#include <iostream>

#include "Event.hpp"

class Gold : public Event {
    void percept() const noexcept override {
        std::cout << "你感到金光闪闪！" << std::endl;
    }
    bool die() const noexcept override {
        return false;
    }
    bool reward() const noexcept override {
        return true;
    }
};
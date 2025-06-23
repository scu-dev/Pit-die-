#include <iostream>

#include "Game.hpp"

int main() noexcept {
    int size = 5;
    Game g(size);
    g.run();
    return 0;
}
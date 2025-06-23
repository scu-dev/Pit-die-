#ifdef _WIN32
    #include <Windows.h>
#endif // _WIN32

#include "Game.hpp"

int main() noexcept {
    #ifdef _WIN32
        SetConsoleOutputCP(CP_UTF8);
        SetConsoleCP(CP_UTF8);
    #endif // _WIN32
    int size = 5;
    cout << "输入《洞穴》大小：";
    cin >> size;
    Game g(size);
    g.run();
    return 0;
}
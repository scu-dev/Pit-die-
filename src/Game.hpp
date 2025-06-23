#pragma once
#include <iostream>
#include <string>
#include <vector>

#include "Player.hpp"
#include "Room.hpp"

using std::string, std::vector, std::cout, std::cin, std::endl;

class Game {
private:
    vector<vector<Room*>> rooms;
    const int size_;
    Player* player_;

public:
    Game(int size) noexcept : size_(size) {
        player_ = new Player();
        for (int i = 0; i < size; i++) {
            vector<Room*> tmp;
            for (int j = 0; j < size; j++) tmp.push_back(new Room());
            rooms.push_back(tmp);
        }
    }
    ~Game() {
        for (int i = 0; i < size_; i++) for(int j = 0; j < size_; j++) if(rooms[i][j] != nullptr) delete rooms[i][j];
    }
    void run() noexcept {
        try {
            show_room();
            player_percept();
            direction();
        } catch (...) {
            cout << "游戏重新开始！" << endl;
            for (auto& row : rooms) for(auto roomptr : row) delete roomptr;
            rooms.clear();
            random_room();
        }
    }
    void random_room() noexcept {
        srand(time(NULL));
        bool havePlayer = false;
        int goldAmount = 2, pitAmount = 10;
        for (int i = 0; i < size_; i++) for(int j = 0; j < size_; j++) {
            if (rand() / (double)RAND_MAX >= 0.5) {
                if (!havePlayer) rooms[i][j] = Room::roomWithPlayer(player_);
                else if (goldAmount > 0) {
                    goldAmount--;
                    rooms[i][j] = Room::roomWithGold();
                }
                else if (pitAmount > 0) {
                    pitAmount--;
                    rooms[i][j] = Room::roomWithPit();
                }
                else rooms[i][j] = Room::roomWithEmpty();
            }
            else rooms[i][j] = Room::roomWithEmpty();
        }
    }
    void show_room() noexcept {
        for (int i = 0; i < size_ * 2 + 1; i++) {
            for (int j = 0; j < size_ * 2 + 1; j++) {
                //模 2 改为按位与 1 快不少
                if ((i & 1) && (j & 1)) rooms[i][j]->show();
                else if (!(i & 1) && (j & 1)) cout << "|";
                else if ((i & 1) && !(j & 1)) cout << "-";
                //只有这四种，可以直接 else
                else cout << "+";
            }
            cout << endl;
        }
    }
    void player_percept() noexcept {
        cout << "请输入想要看的相邻格，tdlr：" << endl;
        string input;
        cin >> input;
        if(input.size() == 1) switch (input[0]) {
            case 't':

                break;
            case 'b':

                break;
            case 'l':

                break;
            case 'r':

                break;
            default:
                cout << "输入不合法，将被判处六个月至一年有期徒刑！" << endl;
                break;
        }
        else cout << "输入不合法，将被判处六个月至一年有期徒刑！" << endl;
    }
    void direction() noexcept {

    }
    void check_end() noexcept {

    }
};
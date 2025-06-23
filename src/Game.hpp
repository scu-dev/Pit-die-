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
    //x 横轴 y 纵轴 (0,0) 左上角
    int x, y, gold;

    bool testforPlayerPosition(char input) const noexcept {
        switch (input) {
            case 't':
                if (x == 0) return false;
                else return true;
            case 'b':
                if (x == size_ - 1) return false;
                else return true;
            case 'l':
                if (y == 0) return false;
                else return true;
            case 'r':
                if (y == size_ - 1) return false;
                else return true;
            default: return false;
        }
    }

    void handleArrive(int newX, int newY) {
        rooms[x][y]->leave();
        x = newX;
        y = newY;
        rooms[x][y]->enter(player_);
        if (rooms[x][y]->hasReward()) {
            cout << "你获得了一个 gold！" << endl;
            gold++;
        }
    }

public:
    Game(int size) noexcept : size_(size), gold(0) {
        player_ = new Player();
        for (int i = 0; i < size; i++) {
            vector<Room*> tmp;
            for (int j = 0; j < size; j++) tmp.resize(size);
            rooms.push_back(tmp);
        }
    }
    ~Game() {
        for (int i = 0; i < size_; i++) for(int j = 0; j < size_; j++) if(rooms[i][j] != nullptr) delete rooms[i][j];
    }
    void run() noexcept {
        random_room();
        while (true) {
            try {
                show_room();
                player_percept();
                input_direction();
            } catch (...) {
                cout << endl << "-----------------\n你 DIE 了！\n你获得了 " << gold << " 个 gold！\n游戏重新开始！\n-----------------" << endl << endl;
                for (auto& row : rooms) for (auto roomptr : row) delete roomptr;
                rooms.clear();
                gold = 0;
                for (int i = 0; i < size_; i++) {
                    vector<Room*> tmp;
                    for (int j = 0; j < size_; j++) tmp.resize(size_);
                    rooms.push_back(tmp);
                }
                random_room();
            }
        }
    }
    void random_room() noexcept {
        srand(time(NULL));
        bool havePlayer = false;
        //挺难的说实话
        int goldAmount = size_ * 2, pitAmount = size_;
        for (int i = 0; i < size_; i++) for(int j = 0; j < size_; j++) {
            if (rand() / (double)RAND_MAX >= 0.5) {
                if (!havePlayer){
                    rooms[i][j] = Room::roomWithPlayer(player_);
                    x = j;
                    y = i;
                    havePlayer = true;
                }
                else if (pitAmount > 0) {
                    rooms[i][j] = Room::roomWithPit();
                    pitAmount--;
                }
                else if (goldAmount > 0) {
                    rooms[i][j] = Room::roomWithGold();
                    goldAmount--;
                }
                else rooms[i][j] = Room::roomWithEmpty();
            }
            else rooms[i][j] = Room::roomWithEmpty();
        }
        if (!havePlayer) {
            delete rooms[0][0];
            rooms[0][0] = Room::roomWithPlayer(player_);
            x = 0;
            y = 0;
        }
    }
    void show_room() noexcept {
        for (int i = 0; i < size_ * 2 + 1; i++) {
            for (int j = 0; j < size_ * 2 + 1; j++) {
                //模 2 改为按位与 1 快不少
                if ((i & 1) && (j & 1)) rooms[(i - 1) / 2][(j - 1) / 2]->show();
                else if (!(i & 1) && (j & 1)) cout << "-";
                else if ((i & 1) && !(j & 1)) cout << "|";
                //只有这四种，可以直接 else
                else cout << "+";
            }
            cout << endl;
        }
    }
    void player_percept() noexcept {
        cout << "请输入想要看的相邻格，tblr：" << endl;
        string input;
        cin >> input;
        if(input.size() == 1) switch (input[0]) {
            case 't':
                if(!testforPlayerPosition(input[0])) cout << "那是无尽的虚空！" << endl;
                else rooms[x - 1][y]->percept();
                break;
            case 'b':
                if (!testforPlayerPosition(input[0])) cout << "那是无尽的虚空！" << endl;
                else rooms[x + 1][y]->percept();
                break;
            case 'l':
                if (!testforPlayerPosition(input[0])) cout << "那是无尽的虚空！" << endl;
                else rooms[x][y - 1]->percept();
                break;
            case 'r':
                if (!testforPlayerPosition(input[0])) cout << "那是无尽的虚空！" << endl;
                else rooms[x][y + 1]->percept();
                break;
            default:
                cout << "输入不合法，将被判处六个月至一年有期徒刑！" << endl;
                break;
        }
        else cout << "输入不合法，将被判处六个月至一年有期徒刑！" << endl;
    }
    void input_direction() {
        cout << "请选择走向何处，tblr：" << endl;
        string input;
        cin >> input;
        if(input.size() == 1) switch (input[0]) {
            case 't':
                if(!testforPlayerPosition(input[0])) cout << "那是不可到达的虚空！" << endl;
                else handleArrive(x - 1, y);
                break;
            case 'b':
                if (!testforPlayerPosition(input[0])) cout << "那是不可到达的虚空！" << endl;
                else handleArrive(x + 1, y);
                break;
            case 'l':
                if (!testforPlayerPosition(input[0])) cout << "那是不可到达的虚空！" << endl;
                else handleArrive(x, y - 1);
                break;
            case 'r':
                if (!testforPlayerPosition(input[0])) cout << "那是不可到达的虚空！" << endl;
                else handleArrive(x, y + 1);
                break;
            default:
                cout << "输入不合法，将被判处六个月至一年有期徒刑！" << endl;
                break;
        }
        else cout << "输入不合法，将被判处六个月至一年有期徒刑！" << endl;
    }
};
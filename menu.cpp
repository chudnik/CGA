#include "menu.h"

#include <conio.h>

#include <iostream>

void setConsoleColor(bool selected) {
    if (selected) {
        std::cout << "\033[7m";
    } else {
        std::cout << "\033[0m";
    }
}

int selectGameType() {
    const char *gameTypeNames[Game::GAME_TYPE_COUNT] = {"POKER", "BLACKJACK", "GO_FISH", "FOOL"};
    int selected = 0;
    while (true) {
        system("cls");
        std::cout << "Select game type using arrow keys and press Enter:\n";
        for (int i = 0; i < Game::GAME_TYPE_COUNT; ++i) {
            setConsoleColor(i == selected);
            std::cout << gameTypeNames[i] << "\n";
            setConsoleColor(false);
        }
        int key = _getch();
        if (key == 224) {
            key = _getch();
            if (key == 72) {
                selected = (selected - 1 + Game::GAME_TYPE_COUNT) % Game::GAME_TYPE_COUNT;
            } else if (key == 80) {
                selected = (selected + 1) % Game::GAME_TYPE_COUNT;
            }
        } else if (key == 13) {
            break;
        }
    }
    return selected;
}
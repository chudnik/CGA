#include <iostream>

#include "card.h"
#include "menu.h"

int main() {
    int gameType = selectGameType();
    Game game(static_cast<Game::Type>(gameType));
    std::cout << "Enter number of players: ";
    int numPlayers;
    std::cin >> numPlayers;
    for (int i = 0; i < numPlayers; i++) {
        std::string playerName;
        if (i == 0) {
            std::cout << "Enter your name: ";
            std::cin >> playerName;
        } else {
            std::cout << "Enter player " << i + 1 << " name: ";
            std::cin >> playerName;
        }
        game.addPlayer(Player(playerName));
    }
    std::cout << "Game created!" << std::endl;
    return 0;
}
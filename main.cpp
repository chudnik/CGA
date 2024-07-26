#include <ncurses.h>

#include <algorithm>
#include <string>
#include <vector>

using namespace std;

class Card {
   public:
    enum Suit { HEARTS, DIAMONDS, CLUBS, SPADES };
    enum Rank { ACE = 1, TWO, THREE, FOUR, FIVE, SIX, SEVEN, EIGHT, NINE, TEN, JACK, QUEEN, KING };
    enum Color { RED, BLACK };

    Card(Suit s, Rank r) : suit(s), rank(r) { color = (suit == HEARTS || suit == DIAMONDS) ? RED : BLACK; }

    Suit getSuit() const { return suit; }
    Rank getRank() const { return rank; }
    Color getColor() const { return color; }

    void print() const {
        const char* suits[] = {"Hearts", "Diamonds", "Clubs", "Spades"};
        const char* ranks[] = {"Ace", "2", "3", "4", "5", "6", "7", "8", "9", "10", "Jack", "Queen", "King"};
        printw("%s of %s\n", ranks[rank - 1], suits[suit]);
    }

    bool operator==(const Card& other) const { return suit == other.suit && rank == other.rank; }

   private:
    Suit suit;
    Rank rank;
    Color color;
};

class Deck {
   public:
    Deck() : countCards(52) {
        for (int s = Card::HEARTS; s <= Card::SPADES; s++) {
            for (int r = Card::ACE; r <= Card::KING; r++) {
                cards.push_back(Card(static_cast<Card::Suit>(s), static_cast<Card::Rank>(r)));
            }
        }
    }

    void removeCard(const Card& card) {
        auto it = find(cards.begin(), cards.end(), card);
        if (it != cards.end()) {
            cards.erase(it);
            countCards--;
        }
    }

    unsigned int getCountCards() const { return countCards; }
    vector<Card> getCards() const { return cards; }

   private:
    unsigned int countCards;
    vector<Card> cards;
};

class Player {
   public:
    Player(const string n) : name(n), countCards(0) {}

    string getName() const { return name; }
    unsigned int getCountCards() const { return countCards; }
    vector<Card> getHand() const { return hand; }

    void addCard(const Card& card) {
        hand.push_back(card);
        countCards++;
    }

    void removeCard(const Card& card) {
        auto it = find(hand.begin(), hand.end(), card);
        if (it != hand.end()) {
            hand.erase(it);
            countCards--;
        }
    }

    void printHand() const {
        printw("%s's hand:\n", name.c_str());
        for (const auto& card : hand) {
            card.print();
        }
    }

   private:
    string name;
    unsigned int countCards;
    vector<Card> hand;
};

class Game {
   public:
    enum GameType { POKER, BLACKJACK, FOOL };

    Game(GameType type, unsigned int count) : gameType(type), countPlayers(count) {}

    GameType getGameType() const { return gameType; }
    unsigned int getCountPlayers() const { return countPlayers; }
    vector<Player> getPlayers() const { return players; }

    void addPlayer(const Player& player) { players.push_back(player); }

   private:
    GameType gameType;
    unsigned int countPlayers;
    vector<Player> players;
};

void displayMenu(int selected, const vector<string>& menuItems) {
    for (int i = 0; i < menuItems.size(); ++i) {
        if (i == selected) {
            attron(A_REVERSE);
            printw("%d. %s\n", i + 1, menuItems[i].c_str());
            attroff(A_REVERSE);
        } else {
            printw("%d. %s\n", i + 1, menuItems[i].c_str());
        }
    }
}

void displayCards(int selected, const vector<Card>& cards) {
    int index = 0;
    for (int i = 0; i < 4; ++i) {
        for (int j = 0; j < 13; ++j) {
            if (index == selected) {
                attron(A_REVERSE);
                cards[index].print();
                attroff(A_REVERSE);
            } else {
                cards[index].print();
            }
            index++;
        }
        printw("\n");
    }
}

void displayPlayers(int selected, const vector<Player>& players) {
    for (int i = 0; i < players.size(); ++i) {
        if (i == selected) {
            attron(A_REVERSE);
            printw("%d. %s\n", i + 1, players[i].getName().c_str());
            attroff(A_REVERSE);
        } else {
            printw("%d. %s\n", i + 1, players[i].getName().c_str());
        }
    }
}

int main() {
    initscr();
    cbreak();
    noecho();
    keypad(stdscr, TRUE);

    Deck deck;
    Game game(Game::POKER, 2);
    game.addPlayer(Player("Alice"));
    game.addPlayer(Player("Bob"));

    int selectedMenu = 0;
    int selectedCard = 0;
    int selectedPlayer = 0;

    vector<string> menuItems = {"Add Card to Player's Hand", "Remove Card from Player's Hand", "Print Player's Hand",
                                "Exit"};

    while (true) {
        clear();
        displayMenu(selectedMenu, menuItems);
        refresh();

        int ch = getch();
        if (ch == KEY_UP) {
            selectedMenu = max(0, selectedMenu - 1);
        } else if (ch == KEY_DOWN) {
            selectedMenu = min(3, selectedMenu + 1);
        } else if (ch == 10) {  // Enter key
            clear();
            if (selectedMenu == 0) {  // Add Card to Player's Hand
                displayPlayers(selectedPlayer, game.getPlayers());
                refresh();

                ch = getch();
                if (ch == KEY_UP) {
                    selectedPlayer = max(0, selectedPlayer - 1);
                } else if (ch == KEY_DOWN) {
                    selectedPlayer = min(static_cast<int>(game.getPlayers().size()) - 1, selectedPlayer + 1);
                } else if (ch == 10) {  // Enter key
                    clear();
                    displayCards(selectedCard, deck.getCards());
                    refresh();

                    ch = getch();
                    if (ch == KEY_UP) {
                        selectedCard = max(0, selectedCard - 13);
                    } else if (ch == KEY_DOWN) {
                        selectedCard = min(51, selectedCard + 13);
                    } else if (ch == KEY_LEFT) {
                        selectedCard = max(0, selectedCard - 1);
                    } else if (ch == KEY_RIGHT) {
                        selectedCard = min(51, selectedCard + 1);
                    } else if (ch == 10) {  // Enter key
                        clear();
                        Card selectedCardObj = deck.getCards()[selectedCard];
                        game.getPlayers()[selectedPlayer].addCard(selectedCardObj);
                        deck.removeCard(selectedCardObj);
                        printw("Card added to %s's hand.\n", game.getPlayers()[selectedPlayer].getName().c_str());
                        refresh();
                        getch();
                    }
                }
            } else if (selectedMenu == 1) {  // Remove Card from Player's Hand
                displayPlayers(selectedPlayer, game.getPlayers());
                refresh();

                ch = getch();
                if (ch == KEY_UP) {
                    selectedPlayer = max(0, selectedPlayer - 1);
                } else if (ch == KEY_DOWN) {
                    selectedPlayer = min(static_cast<int>(game.getPlayers().size()) - 1, selectedPlayer + 1);
                } else if (ch == 10) {  // Enter key
                    clear();
                    displayCards(selectedCard, game.getPlayers()[selectedPlayer].getHand());
                    refresh();

                    ch = getch();
                    if (ch == KEY_UP) {
                        selectedCard = max(0, selectedCard - 13);
                    } else if (ch == KEY_DOWN) {
                        selectedCard = min(static_cast<int>(game.getPlayers()[selectedPlayer].getHand().size()) - 1,
                                           selectedCard + 13);
                    } else if (ch == KEY_LEFT) {
                        selectedCard = max(0, selectedCard - 1);
                    } else if (ch == KEY_RIGHT) {
                        selectedCard = min(static_cast<int>(game.getPlayers()[selectedPlayer].getHand().size()) - 1,
                                           selectedCard + 1);
                    } else if (ch == 10) {  // Enter key
                        clear();
                        Card selectedCardObj = game.getPlayers()[selectedPlayer].getHand()[selectedCard];
                        game.getPlayers()[selectedPlayer].removeCard(selectedCardObj);
                        printw("Card removed from %s's hand.\n", game.getPlayers()[selectedPlayer].getName().c_str());
                        refresh();
                        getch();
                    }
                }
            } else if (selectedMenu == 2) {  // Print Player's Hand
                displayPlayers(selectedPlayer, game.getPlayers());
                refresh();

                ch = getch();
                if (ch == KEY_UP) {
                    selectedPlayer = max(0, selectedPlayer - 1);
                } else if (ch == KEY_DOWN) {
                    selectedPlayer = min(static_cast<int>(game.getPlayers().size()) - 1, selectedPlayer + 1);
                } else if (ch == 10) {  // Enter key
                    clear();
                    game.getPlayers()[selectedPlayer].printHand();
                    refresh();
                    getch();
                }
            } else if (selectedMenu == 3) {  // Exit
                break;
            }
        }
    }

    endwin();
    return 0;
}
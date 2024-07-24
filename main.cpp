#include <iostream>
#include <vector>
using namespace std;

class Card {
   public:
    enum Suit { HEARTS, DIAMONDS, CLUBS, SPADES };
    enum Rank { ACE = 1, TWO, THREE, FOUR, FIVE, SIX, SEVEN, EIGHT, NINE, TEN, JACK, QUEEN, KING };
    enum Color { RED, BLACK };

    Card(Suit s, Rank r) : suit(s), rank(r) { color = static_cast<Color>(suit / 2); }

    Suit getSuit() const { return suit; }
    Rank getRank() const { return rank; }
    Color getColor() const { return color; }

    void print() const {
        const char *suits[] = {"Hearts", "Diamonds", "Clubs", "Spades"};
        const char *ranks[] = {"Ace", "2", "3", "4", "5", "6", "7", "8", "9", "10", "Jack", "Queen", "King"};
        cout << ranks[rank - 1] << " of " << suits[suit] << endl;
    }

   private:
    Suit suit;
    Rank rank;
    Color color;
};

class Player {
   public:
    Player(const string n) : name(n) {}
    void printHand() const {
        cout << name << "'s hand:" << endl;
        for (const auto &card : hand) {
            card.print();
        }
    }

   private:
    string name;
    vector<Card> hand;
};

class Game {
   public:
    enum GameType { POKER, BLACKJACK, FOOL };

   private:
    GameType gameType;
    vector<>
};

int main() {
    cout << "Enter game type: ";
    return 0;
}
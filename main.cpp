#include <algorithm>
#include <iostream>
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
        const char *suits[] = {"Hearts", "Diamonds", "Clubs", "Spades"};
        const char *ranks[] = {"Ace", "2", "3", "4", "5", "6", "7", "8", "9", "10", "Jack", "Queen", "King"};
        cout << ranks[rank - 1] << " of " << suits[suit] << endl;
    }

    bool operator==(const Card &other) const { return suit == other.suit && rank == other.rank; }

   private:
    Suit suit;
    Rank rank;
    Color color;
};

class Deck {
   public:
    Deck() : countCards(52) {
        for (int s = Card::HEARTS; s < Card::SPADES; s++) {
            for (int r = Card::ACE; r < Card::KING; r++) {
                cards.push_back(Card(static_cast<Card::Suit>(s), static_cast<Card::Rank>(r)));
            }
        }
    }

    void removeCard(const Card &card) {
        auto it = find(cards.begin(), cards.end(), card);
        if (it != cards.end()) {
            cards.erase(it);
            countCards--;
        }
    }

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

    void addCard(const Card &card) {
        hand.push_back(card);
        countCards++;
    }

    void removeCard(const Card &card) {
        auto it = find(hand.begin(), hand.end(), card);
        if (it != hand.end()) {
            hand.erase(it);
            countCards--;
        }
    }

    void printHand() const {
        cout << name << "'s hand:" << endl;
        for (const auto &card : hand) {
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

   private:
    GameType gameType;
    unsigned int countPlayers;
    vector<Player> players;
};

int main() {
    cout << "Enter game type: ";
    return 0;
}
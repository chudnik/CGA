#ifndef CARD_H
#define CARD_H

#include <iostream>
#include <vector>

class Card {
public:
    enum Suit {
        HEARTS, DIAMONDS, CLUBS, SPADES
    };
    enum Rank {
        ACE = 1, TWO, THREE, FOUR, FIVE, SIX, SEVEN, EIGHT, NINE, TEN, JACK, QUEEN, KING
    };
    enum Color {
        RED, BLACK
    };

    Card(Suit s, Rank r) : suit(s), rank(r) { color = static_cast<Color>(suit / 2); }

    Suit getSuit() const { return suit; }

    Rank getRank() const { return rank; }

    Color getColor() const { return color; }

    void print() const {
        const char *suits[] = {"Hearts", "Diamonds", "Clubs", "Spades"};
        const char *ranks[] = {"Ace", "2", "3", "4", "5", "6", "7", "8", "9", "10", "Jack", "Queen", "King"};
        std::cout << ranks[rank - 1] << " of " << suits[suit] << std::endl;
    }

    bool operator==(const Card &other) const { return suit == other.suit && rank == other.rank; }

private:
    Rank rank;
    Suit suit;
    Color color;
};

class Player {
private:
    std::string name;
    std::vector<Card> hand;

public:
    explicit Player(std::string playerName) { name = std::move(playerName); }

    void drawCard(Card card) { hand.push_back(card); }

    void removeCard(const Card &card) {
        for (auto it = hand.begin(); it != hand.end(); ++it) {
            if (*it == card) {
                hand.erase(it);
                break;
            }
        }
    }

    void print() {
        std::cout << name << "'s hand:" << std::endl;
        for (auto i: hand) {
            i.print();
        }
    }

    bool operator==(const Player &other) const { return name == other.name && hand == other.hand; }
};

class Deck {
private:
    std::vector<Card> cards;

public:
    Deck() {
        for (int s = Card::HEARTS; s <= Card::SPADES; s++) {
            for (int r = Card::ACE; r <= Card::KING; r++) {
                cards.emplace_back(static_cast<Card::Suit>(s), static_cast<Card::Rank>(r));
            }
        }
    }

    void removeCard(const Card &card) {
        for (auto it = cards.begin(); it != cards.end(); ++it) {
            if (*it == card) {
                cards.erase(it);
                break;
            }
        }
    }

    void print() {
        std::cout << "Deck:" << std::endl;
        for (int i = 0; i < cards.size(); i++) {
            cards[i].print();
        }
    }
};

class Table {
private:
    std::vector<Card> cards;

public:
    void addCard(Card card) { cards.push_back(card); }

    void printTable() {
        std::cout << "Table:" << std::endl;
        for (auto card: cards) {
            card.print();
        }
    }
};

class Game {
public:
    enum Type {
        POKER, BLACKJACK, GO_FISH, FOOL, GAME_TYPE_COUNT
    };

    explicit Game(Type t) : gameType(t) {}

    Type getGameType() const { return gameType; }

    Deck getDeck() const { return deck; }

    std::vector<Player> getPlayers() const { return players; }

    void addPlayer(const Player &player) { players.push_back(player); }

    void removePlayer(const Player &player) {
        for (auto it = players.begin(); it != players.end(); ++it) {
            if (*it == player) {
                players.erase(it);
                break;
            }
        }
    }

private:
    Type gameType;
    Deck deck;
    std::vector<Player> players;
};

#endif
#pragma once
#include <vector>
#include <string>

struct Card {
    std::string rank;
    std::string suit;
    int value;
    std::string toString() const;
};

class Deck {
private:
    std::vector<Card> cards;
public:
    void initialize();
    void shuffle();
    std::vector<Card> draw(int count);
};

class RunSession {
private:
    Deck deck;
    int currentRound;
    const int MAX_ROUNDS = 5;

    bool playRound();

public:
    RunSession();
    void start();
};
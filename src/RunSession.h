#pragma once
#include <vector>
#include <string>
#include "Card.h"
#include "ScoringSystem.h"

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
    ScoringSystem scoringSystem; // Integrasi sistem skor
    int currentRound;
    const int MAX_ROUNDS = 5;
    float totalRunScore;
    float targetScore;

    bool playRound();

public:
    RunSession();
    void start();
};
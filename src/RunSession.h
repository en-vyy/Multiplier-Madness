#pragma once
#include <vector>
#include <string>
#include "Card.h"
#include "ScoringSystem.h"
#include "ShopSystem.h" // Tambahan baru

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
    ScoringSystem scoringSystem;
    ShopSystem shopSystem; // Tambahan baru
    int currentRound;
    const int MAX_ROUNDS = 5;
    float totalRunScore;
    float targetScore;
    
    int playerGold; // Uang pemain
    int totalModifiersBought; // Melacak jumlah item

    bool playRound();

public:
    RunSession();
    void start();
};
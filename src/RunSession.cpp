#include "RunSession.h"
#include <iostream>
#include <cstdlib>
#include <algorithm>

std::string Card::toString() const {
    return rank + " of " + suit + " (Val: " + std::to_string(value) + ")";
}

void Deck::initialize() {
    cards.clear();
    std::string suits[] = {"Hearts", "Diamonds", "Clubs", "Spades"};
    std::string ranks[] = {"2","3","4","5","6","7","8","9","10","J","Q","K","A"};
    int values[] = {2, 3, 4, 5, 6, 7, 8, 9, 10, 10, 10, 10, 11};
    for(const auto& suit : suits) {
        for(int i = 0; i < 13; ++i) { cards.push_back({ranks[i], suit, values[i]}); }
    }
}

void Deck::shuffle() {
    for (size_t i = 0; i < cards.size(); i++) {
        size_t r = rand() % cards.size();
        std::swap(cards[i], cards[r]);
    }
}

std::vector<Card> Deck::draw(int count) {
    std::vector<Card> hand;
    for(int i = 0; i < count && !cards.empty(); ++i) {
        hand.push_back(cards.back());
        cards.pop_back();
    }
    return hand;
}

// === PERUBAHAN COMMIT 2 ADA DI BAWAH INI ===

RunSession::RunSession() : scoringSystem(std::make_unique<StandardScoring>()), currentRound(1), totalRunScore(0), targetScore(150.0f) {
    deck.initialize();
    deck.shuffle();
}

void RunSession::start() {
    std::cout << "=== WELCOME TO MULTIPLIER MADNESS ===\n";
    while (currentRound <= MAX_ROUNDS) {
        if (!playRound()) {
            std::cout << "\n[ GAME OVER ] You failed to reach the target score!\n";
            return; 
        }
        
        // Target skor disesuaikan untuk murni kombinasi kartu (playable tanpa modifier)
        if (currentRound == 1) targetScore = 300.0f;
        else if (currentRound == 2) targetScore = 600.0f;
        else if (currentRound == 3) targetScore = 900.0f;
        else if (currentRound == 4) targetScore = 1200.0f;
        
        currentRound++;
    }
    std::cout << "\n=== YOU WIN! RUN COMPLETED ===\n";
    std::cout << "Total Final Run Score: " << totalRunScore << "\n";
}

bool RunSession::playRound() {
    std::cout << "\n--- ROUND " << currentRound << " OF " << MAX_ROUNDS << " ---\n";
    std::cout << "TARGET SCORE TO BEAT: " << targetScore << "\n";
    
    std::vector<Card> hand = deck.draw(5);
    if (hand.empty()) {
        deck.initialize(); deck.shuffle();
        hand = deck.draw(5); 
    }

    std::cout << "\nYour Hand:\n";
    for (size_t i = 0; i < hand.size(); ++i) {
        std::cout << "[" << i + 1 << "] " << hand[i].toString() << "\n";
    }

    int numCardsToPlay = 0;
    while (numCardsToPlay < 1 || numCardsToPlay > hand.size()) {
        std::cout << "\nHow many cards do you want to play? (1-" << hand.size() << "): ";
        std::cin >> numCardsToPlay;
    }

    std::vector<Card> playedCards;
    for (int i = 0; i < numCardsToPlay; ++i) {
        int cardIndex = 0;
        while (cardIndex < 1 || cardIndex > hand.size()) {
            std::cout << "Select card index for slot " << (i + 1) << ": ";
            std::cin >> cardIndex;
        }
        playedCards.push_back(hand[cardIndex - 1]);
    }

    std::cout << "\nYou played:\n";
    for(const auto& c : playedCards) {
        std::cout << "- " << c.toString() << "\n";
    }
    
    // Ini yang memanggil kombinasi Blackjack/Full Color dari ScoringSystem
    float roundScore = scoringSystem.calculateTotalScore(playedCards);
    totalRunScore += roundScore;
    std::cout << ">>> FINAL ROUND SCORE: " << roundScore << " <<<\n";

    if (roundScore < targetScore) {
        return false; 
    }
    std::cout << "You beat the target!\n";

    return true; 
}
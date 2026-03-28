#include "ScoringSystem.h"
#include <iostream>
#include <algorithm> // Dibutuhkan untuk std::stable_sort

std::string StandardScoring::getColor(const std::string& suit) {
    if (suit == "Hearts" || suit == "Diamonds") return "Red";
    return "Black";
}

float StandardScoring::calculateBaseScore(const std::vector<Card>& playedCards) {
    if (playedCards.empty()) return 0;

    int totalChips = 0;
    bool allEven = true;
    bool allOdd = true;
    bool allSameColor = true;

    std::string firstColor = getColor(playedCards[0].suit);

    for(const auto& card : playedCards) {
        totalChips += card.value;
        if(card.value % 2 == 0) allOdd = false;
        else allEven = false;
        if(getColor(card.suit) != firstColor) allSameColor = false;
    }

    float multiplier = 5.0f; 
    std::string comboName = "Basic Attack";

    if (totalChips == 21) {
        multiplier = 50.0f;
        comboName = "Lucky 21!";
    } else if (allSameColor && playedCards.size() >= 3) {
        multiplier = 30.0f;
        comboName = "Color Unity (All " + firstColor + ")";
    } else if (allEven && playedCards.size() >= 3) {
        multiplier = 25.0f;
        comboName = "Even Resonance";
    } else if (allOdd && playedCards.size() >= 3) {
        multiplier = 20.0f;
        comboName = "Odd Resonance";
    }

    std::cout << "\n[Scoring] Combo Activated: " << comboName << " (Multiplier: x" << multiplier << ")\n";
    std::cout << "[Scoring] Base Chips: " << totalChips << "\n";
    
    return totalChips * multiplier; 
}

ScoringSystem::ScoringSystem(std::unique_ptr<IScoringStrategy> strat) 
    : strategy(std::move(strat)) {}

// Fungsi untuk memasukkan item ke dalam sistem
void ScoringSystem::addModifier(std::unique_ptr<IModifier> mod) {
    if(mod) activeModifiers.push_back(std::move(mod));
}

float ScoringSystem::calculateTotalScore(const std::vector<Card>& playedCards) {
    float score = strategy->calculateBaseScore(playedCards);
    std::cout << "\n[Scoring] Base score from cards: " << score << "\n";

    // MENGURUTKAN ITEM BERDASARKAN PRIORITAS (1, 2, 3)
    std::stable_sort(activeModifiers.begin(), activeModifiers.end(),
        [](const std::unique_ptr<IModifier>& a, const std::unique_ptr<IModifier>& b) {
            return a->getPriority() < b->getPriority();
        });

    // MENGHITUNG EFEK ITEM
    for(const auto& mod : activeModifiers) {
        mod->apply(score);
        std::cout << "[Scoring] Applied " << mod->getName() << " -> New Score: " << score << "\n";
    }
    return score;
}
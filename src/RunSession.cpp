#include "RunSession.h"
#include "ModifierFactory.h" // Wajib dipanggil untuk menerjemahkan hasil belanja
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

// Cari baris ini dan ubah targetScore menjadi 300.0f, playerGold menjadi 15
RunSession::RunSession() : scoringSystem(std::make_unique<StandardScoring>()), currentRound(1), totalRunScore(0), targetScore(300.0f), playerGold(15), totalModifiersBought(0) {
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
        
        // Target skor diseimbangkan agar mulus
        if (currentRound == 1) targetScore = 1200.0f;
        else if (currentRound == 2) targetScore = 4000.0f;
        else if (currentRound == 3) targetScore = 15000.0f;
        else if (currentRound == 4) targetScore = 100000.0f; // Akan sangat mudah kalau punya Square (^2)
        
        currentRound++;
    }
    std::cout << "\n=== YOU WIN! LEGENDARY RUN COMPLETED ===\n";
    std::cout << "Total Final Run Score: " << totalRunScore << "\n";
    std::cout << "Total Modifiers Accumulated: " << totalModifiersBought << "\n";
}

bool RunSession::playRound() {
    std::cout << "\n====================================\n";
    std::cout << "--- ROUND " << currentRound << " OF " << MAX_ROUNDS << " ---\n";
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

    float roundScore = scoringSystem.calculateTotalScore(playedCards);
    totalRunScore += roundScore;
    std::cout << ">>> FINAL ROUND SCORE: " << roundScore << " <<<\n";

    if (roundScore < targetScore) {
        return false; 
    }

    // --- SISTEM EKONOMI BARU ---
    // Base 15 Gold + Bonus yang lebih cepat naik (dibagi 50, bukan 100)
    int goldEarned = 15 + static_cast<int>((roundScore - targetScore) / 50);
    playerGold += goldEarned;
    std::cout << "You beat the target! Earned " << goldEarned << " Gold.\n";

    // --- FASE TOKO ---
    if (currentRound < MAX_ROUNDS) {
        std::cout << "\n[ Entering Shop Phase ]\n";
        while (true) {
            int choice = shopSystem.browseShop(playerGold);
            if (choice > 0 && choice <= 3) {
                // Pabrik membuat item berdasarkan pilihan dari Toko
                auto newMod = ModifierFactory::createModifier(choice);
                scoringSystem.addModifier(std::move(newMod));
                totalModifiersBought++;
                std::cout << "Modifier active! Total modifiers equipped: " << totalModifiersBought << "\n";
            } else if (choice == 0) {
                std::cout << "Leaving shop...\n";
                break; 
            }
        }
    }
    return true; 
}
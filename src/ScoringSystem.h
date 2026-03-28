#pragma once
#include <vector>
#include <memory>
#include "Card.h"
#include "modifiers/IModifier.h"

class IScoringStrategy {
public:
    virtual float calculateBaseScore(const std::vector<Card>& playedCards) = 0;
    virtual ~IScoringStrategy() = default;
};

class StandardScoring : public IScoringStrategy {
private:
    std::string getColor(const std::string& suit);
public:
    float calculateBaseScore(const std::vector<Card>& playedCards) override;
};

class ScoringSystem {
private:
    std::unique_ptr<IScoringStrategy> strategy;
    // Wadah untuk menyimpan item-item yang aktif
    std::vector<std::unique_ptr<IModifier>> activeModifiers; 

public:
    ScoringSystem(std::unique_ptr<IScoringStrategy> strat);
    void addModifier(std::unique_ptr<IModifier> mod); // Fungsi tambah item
    float calculateTotalScore(const std::vector<Card>& playedCards);
};
#pragma once
#include <vector>
#include <memory>
#include "Card.h"

// Behavioral Pattern: Strategy
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

public:
    ScoringSystem(std::unique_ptr<IScoringStrategy> strat);
    float calculateTotalScore(const std::vector<Card>& playedCards);
};
#pragma once
#include "IModifier.h"

class DoubleScoreModifier : public IModifier {
public:
    void apply(float& currentScore) override;
    std::string getName() const override;
    int getPriority() const override;
};
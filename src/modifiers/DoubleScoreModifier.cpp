#include "DoubleScoreModifier.h"

void DoubleScoreModifier::apply(float& currentScore) { currentScore *= 2.0f; }
std::string DoubleScoreModifier::getName() const { return "Double Score (x2)"; }
int DoubleScoreModifier::getPriority() const { return 2; } // Prioritas 2: Lalu kali
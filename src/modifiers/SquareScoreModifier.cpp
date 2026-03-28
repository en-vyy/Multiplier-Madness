#include "SquareScoreModifier.h"

void SquareScoreModifier::apply(float& currentScore) { currentScore *= currentScore; }
std::string SquareScoreModifier::getName() const { return "Square Score (^2)"; }
int SquareScoreModifier::getPriority() const { return 3; } // Prioritas 3: Terakhir pangkat
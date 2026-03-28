#include "FlatBonusModifier.h"

void FlatBonusModifier::apply(float& currentScore) { currentScore += 500.0f; }
std::string FlatBonusModifier::getName() const { return "Flat Bonus (+500)"; }
int FlatBonusModifier::getPriority() const { return 1; } // Prioritas 1: Tambah dulu
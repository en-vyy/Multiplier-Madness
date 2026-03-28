#include "ModifierFactory.h"
#include "modifiers/FlatBonusModifier.h"
#include "modifiers/DoubleScoreModifier.h"
#include "modifiers/SquareScoreModifier.h"

std::unique_ptr<IModifier> ModifierFactory::createModifier(int choice) {
    switch(choice) {
        case 1: return std::make_unique<FlatBonusModifier>();
        case 2: return std::make_unique<DoubleScoreModifier>();
        case 3: return std::make_unique<SquareScoreModifier>();
        default: return nullptr;
    }
}
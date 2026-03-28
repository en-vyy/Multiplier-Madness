#pragma once
#include <memory>
#include "modifiers/IModifier.h"

// Creational Pattern: Factory
class ModifierFactory {
public:
    static std::unique_ptr<IModifier> createModifier(int choice);
};
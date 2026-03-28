#pragma once
#include <string>

// Interface untuk semua Modifier (Structural Pattern: Decorator-like)
class IModifier {
public:
    virtual void apply(float& currentScore) = 0; 
    virtual std::string getName() const = 0;
    virtual int getPriority() const = 0; 
    virtual ~IModifier() = default;
};
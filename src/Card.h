#pragma once
#include <string>

struct Card {
    std::string rank;
    std::string suit;
    int value;
    std::string toString() const;
};
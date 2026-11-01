#pragma once
#include "RouletteNumber.hpp"
#include <random>

class RouletteWheel {
private:
    std::mt19937 generator; 
    std::uniform_int_distribution<int> distribution;

public:
    explicit RouletteWheel(unsigned int seed);

    RouletteNumber spin();
};
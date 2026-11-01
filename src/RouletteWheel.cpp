#include "RouletteWheel.hpp"

RouletteWheel::RouletteWheel(unsigned int seed) 
    : generator(seed), distribution(0, 36) {}

RouletteNumber RouletteWheel::spin() {

    int randomNumber = distribution(generator);
    return RouletteNumber(randomNumber);
}
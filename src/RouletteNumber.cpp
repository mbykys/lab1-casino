#include "RouletteNumber.hpp"

RouletteNumber::RouletteNumber(int val) {
    if (val < 0 || val > 36) {
        throw std::invalid_argument("Число на рулетке должно быть от 0 до 36");
    }
    value = val;
    color = determineColor(val);
}

RouletteColor RouletteNumber::determineColor(int number) const {
    if (number == 0) return RouletteColor::Green;
    
    if ((number >= 1 && number <= 10) || (number >= 19 && number <= 28)) {
        return (number % 2 != 0) ? RouletteColor::Red : RouletteColor::Black;
    } else {
        return (number % 2 != 0) ? RouletteColor::Black : RouletteColor::Red;
    }
}

int RouletteNumber::getValue() const {
    return value;
}

RouletteColor RouletteNumber::getColor() const {
    return color;
}

std::string RouletteNumber::getColorName() const {
    switch (color) {
        case RouletteColor::Red: return "Красное";
        case RouletteColor::Black: return "Черное";
        case RouletteColor::Green: return "Зеленое";
        default: return "Неизвестно";
    }
}
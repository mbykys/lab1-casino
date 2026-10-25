#pragma once
#include <stdexcept>
#include <string>

enum class RouletteColor {
    Red,
    Black,
    Green
};

class RouletteNumber {
private:
    int value;
    RouletteColor color;
    
    RouletteColor determineColor(int number) const;

public:
    explicit RouletteNumber(int val);
    
    int getValue() const;
    RouletteColor getColor() const;
    std::string getColorName() const;
};
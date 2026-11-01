#include "Bet.hpp"
#include <stdexcept>

Bet::Bet(const Money& betAmount) : amount(betAmount) {}

Money Bet::getAmount() const { return amount; }


ColorBet::ColorBet(const Money& betAmount, RouletteColor color) : Bet(betAmount), chosenColor(color) {
    if (color == RouletteColor::Green) {
        throw std::invalid_argument("Нельзя ставить на зеленый цвет. Ставьте на число 0.");
    }
}

bool ColorBet::isWinning(const RouletteNumber& winningNumber) const {
    return winningNumber.getColor() == chosenColor;
}

Money ColorBet::calculatePayout() const {
    return Money(amount.getAmount() * 2);
}


NumberBet::NumberBet(const Money& betAmount, int number) : Bet(betAmount), chosenNumber(number) {
    if (number < 0 || number > 36) {
        throw std::invalid_argument("Число для ставки должно быть от 0 до 36");
    }
}

bool NumberBet::isWinning(const RouletteNumber& winningNumber) const {
    return winningNumber.getValue() == chosenNumber;
}

Money NumberBet::calculatePayout() const {
    return Money(amount.getAmount() * 36);
}
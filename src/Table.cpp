#include "Table.hpp"

Table::Table(const Money& minBetLimit, const Money& maxBetLimit) : minBet(minBetLimit), maxBet(maxBetLimit) {    if (minBet.getAmount() > maxBet.getAmount()) {
        throw std::invalid_argument("Мин ставка не может быть больше макс");
    }
}

Money Table::getMinBet() const { return minBet; }
Money Table::getMaxBet() const { return maxBet; }

void Table::validateBet(const Money& betAmount) const {
    if (betAmount.getAmount() < minBet.getAmount()) {
        throw std::invalid_argument("Ставка меньше минимальной"); 
    }
    if (betAmount.getAmount() > maxBet.getAmount()) {
        throw std::invalid_argument("Ставка больше максимальной"); 
    }
}
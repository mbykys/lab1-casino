#pragma once
#include "Money.hpp"
#include <stdexcept>

class Table {
    private:
    Money minBet;
    Money maxBet;

    public:
    Table(const Money& minBetLimit, const Money& maxBetLimit);

    Money getMinBet() const;
    Money getMaxBet() const;

    void validateBet(const Money& BetAmount) const;
};
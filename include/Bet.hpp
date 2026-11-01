#pragma once
#include "Money.hpp"
#include "RouletteNumber.hpp"

class Bet {
protected:
    Money amount; 

public:
    explicit Bet(const Money& betAmount);
    virtual ~Bet() = default; 

    Money getAmount() const;

    virtual bool isWinning(const RouletteNumber& winningNumber) const = 0;
    virtual Money calculatePayout() const = 0;
};

class ColorBet : public Bet {
private:
    RouletteColor chosenColor;

public:
    ColorBet(const Money& betAmount, RouletteColor color);
    
    bool isWinning(const RouletteNumber& winningNumber) const override;
    Money calculatePayout() const override;
};

class NumberBet : public Bet {
private:
    int chosenNumber;

public:
    NumberBet(const Money& betAmount, int number);
    
    bool isWinning(const RouletteNumber& winningNumber) const override;
    Money calculatePayout() const override;
};
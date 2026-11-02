#pragma once
#include "Bet.hpp"
#include "Table.hpp"
#include "Player.hpp"
#include <memory>

class BotStrategy {
public:
    virtual ~BotStrategy() = default;
    
    virtual std::unique_ptr<Bet> generateBet(const Table& table, const Player& player) = 0;
    
    virtual void updateFeedback(bool won) = 0;
};

class MartingaleStrategy : public BotStrategy {
private:
    Money baseBetAmount;
    Money currentBetAmount;
    RouletteColor preferredColor;

public:
    MartingaleStrategy(const Money& baseBet, RouletteColor color);
    
    std::unique_ptr<Bet> generateBet(const Table& table, const Player& player) override;
    void updateFeedback(bool won) override;
};
#include "BotStrategy.hpp"

MartingaleStrategy::MartingaleStrategy(const Money& baseBet, RouletteColor color)
    : baseBetAmount(baseBet), currentBetAmount(baseBet), preferredColor(color) {}

std::unique_ptr<Bet> MartingaleStrategy::generateBet(const Table& table, const Player& player) {
    int amountToBet = currentBetAmount.getAmount();

    if (amountToBet > player.getBalance().getAmount()) {
        amountToBet = player.getBalance().getAmount();
    }
    
    if (amountToBet > table.getMaxBet().getAmount()) {
        amountToBet = table.getMaxBet().getAmount();
    }

    if (amountToBet < table.getMinBet().getAmount()) {
        return nullptr; 
    }

    return std::make_unique<ColorBet>(Money(amountToBet), preferredColor);
}

void MartingaleStrategy::updateFeedback(bool won) {
    if (won) {
        currentBetAmount = baseBetAmount; 
    } else {
        currentBetAmount = Money(currentBetAmount.getAmount() * 2); 
    }
}
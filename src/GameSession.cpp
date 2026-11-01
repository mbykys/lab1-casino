#include "GameSession.hpp"
#include <stdexcept>

GameSession::GameSession(Player& p, CasinoBank& b, const Table& t, RouletteWheel& w) : player(p), bank(b), table(t), wheel(w) {}

RouletteNumber GameSession::playRound(const Bet& bet) {
    table.validateBet(bet.getAmount());

    Money potentialBankLoss(bet.calculatePayout().getAmount() - bet.getAmount().getAmount());
    if (bank.getBalance().getAmount() < potentialBankLoss.getAmount()) {
        throw std::runtime_error("В кассе недостаточно средств для выплаты потенциального выигрыша. Игра остановлена.");
    }

    player.withdraw(bet.getAmount());

    RouletteNumber winningNumber = wheel.spin();

    if (bet.isWinning(winningNumber)) {

        bank.withdraw(potentialBankLoss);
        player.deposit(bet.calculatePayout());
    } else {
        bank.deposit(bet.getAmount());
    }

    return winningNumber;
}
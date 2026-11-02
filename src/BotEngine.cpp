#include "BotEngine.hpp"
#include <iostream>

BotEngine::BotEngine(GameSession& s, Player& p, const Table& t, CasinoBank& b, BotStrategy& strat, GameJournal& j,
                     int spins, const Money& target, const Money& limit)
    : session(s), player(p), table(t), bank(b), strategy(strat), journal(j), 
      maxSpins(spins), winTarget(target), lossLimit(limit) {}

void BotEngine::run() {
    std::cout << "\n[БОТ] Запуск автоматической сессии...\n";
    
    for (int i = 1; i <= maxSpins; ++i) {
        if (player.getBalance().getAmount() >= winTarget.getAmount()) {
            std::cout << "[БОТ] Остановка: достигнута цель по выигрышу (" << player.getBalance().getAmount() << ")\n";
            break;
        }
        if (player.getBalance().getAmount() <= lossLimit.getAmount()) {
            std::cout << "[БОТ] Остановка: достигнут лимит потерь (Осталось " << player.getBalance().getAmount() << ")\n";
            break;
        }

        auto bet = strategy.generateBet(table, player);
        if (!bet) {
            std::cout << "[БОТ] Остановка: бот не может сделать ставку (недостаточно средств или лимиты стола).\n";
            break;
        }

        std::cout << "[БОТ] Спин " << i << ": ставка " << bet->getAmount().getAmount() << "\n";

        try {
            RouletteNumber outcome = session.playRound(*bet);
            bool won = bet->isWinning(outcome);
            
            Money payout(0);
            if (won) {
                payout = bet->calculatePayout();
                std::cout << "      Победа! Выпало " << outcome.getColorName() << "\n";
            } else {
                std::cout << "      Проигрыш. Выпало " << outcome.getColorName() << "\n";
            }
            
            journal.addRecord("Бот (Мартингейл)", outcome, payout, player.getBalance(), bank.getBalance());
            
            strategy.updateFeedback(won);
            
        } catch (const std::exception& e) {
            std::cerr << "[БОТ] Ошибка во время спина: " << e.what() << "\n";
            break;
        }
    }
    std::cout << "[БОТ] Сессия завершена. Итоговый баланс: " << player.getBalance().getAmount() << "\n";
}
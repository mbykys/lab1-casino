#include <iostream>
#include <memory>
#include <limits>
#include <string>
#include "Player.hpp"
#include "CasinoBank.hpp"
#include "Table.hpp"
#include "RouletteWheel.hpp"
#include "GameSession.hpp"
#include "Bet.hpp"
#include "GameJournal.hpp"
#include "BotStrategy.hpp" 
#include "BotEngine.hpp" 

void clearInput() {
    std::cin.clear();
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}

int main() {
    std::cout << "==================================================\n";
    std::cout << "       СИМУЛЯТОР ЕВРОПЕЙСКОЙ РУЛЕТКИ (v1.0)       \n";
    std::cout << "==================================================\n\n";

    std::cout << "Введите имя игрока (или бота):\n> ";
    std::string playerName;
    std::cin >> playerName;

    std::cout << "Стартовый баланс:\n> ";
    int initialBalance;
    while (!(std::cin >> initialBalance) || initialBalance <= 0) {
        clearInput();
        std::cout << "Ошибка! Введите положительное число:\n> ";
    }

    std::cout << "Начальное значение генератора (seed):\n> ";
    unsigned int seed;
    while (!(std::cin >> seed)) {
        clearInput();
        std::cout << "Ошибка! Введите целое число:\n> ";
    }

    // Инициализация общих компонентов
    Player player(playerName, Money(initialBalance));
    CasinoBank bank(Money(1000000));
    Table table(Money(100), Money(10000)); 
    RouletteWheel wheel(seed);
    GameSession session(player, bank, table, wheel);
    GameJournal journal;

    std::cout << "\n=== Выберите режим игры ===\n";
    std::cout << "1. Ручной режим\n";
    std::cout << "2. Автоматическая симуляция (Бот Мартингейл)\n> ";
    
    int mode;
    while (!(std::cin >> mode) || (mode != 1 && mode != 2)) {
        clearInput();
        std::cout << "Введите 1 или 2:\n> ";
    }

    if (mode == 2) {
        std::cout << "\n--- Настройка Бота ---\n";
        
        std::cout << "Количество вращений:\n> ";
        int spins;
        std::cin >> spins;

        std::cout << "Цель по выигрышу (остановиться, если баланс достигнет...):\n> ";
        int target;
        std::cin >> target;

        std::cout << "Лимит потерь (остановиться, если баланс упадет до...):\n> ";
        int limit;
        std::cin >> limit;

        std::cout << "Базовая ставка для Мартингейла (например, 100):\n> ";
        int baseBet;
        std::cin >> baseBet;

        MartingaleStrategy botStrategy(Money(baseBet), RouletteColor::Red);
        BotEngine engine(session, player, table, bank, botStrategy, journal, spins, Money(target), Money(limit));
        
        engine.run();
    } 
    else {
        while (true) {
            std::cout << "--------------------------------------------------\n";
            std::cout << "[Баланс] " << player.getName() << ": " << player.getBalance().getAmount() << " | "
                      << "Касса: " << bank.getBalance().getAmount() << "\n";
            
            if (player.getBalance().getAmount() == 0) {
                std::cout << "Баланс равен нулю. Игра окончена!\n";
                break;
            }

            std::cout << "1. На цвет (1:1)\n2. На число (35:1)\n0. Выйти\n> ";
            int choice;
            if (!(std::cin >> choice)) { clearInput(); continue; }
            if (choice == 0) break;
            if (choice != 1 && choice != 2) continue;

            std::cout << "Сумма ставки:\n> ";
            int betAmount;
            if (!(std::cin >> betAmount)) { clearInput(); continue; }

            std::unique_ptr<Bet> currentBet;
            std::string betDescription;

            try {
                if (choice == 1) {
                    std::cout << "Цвет (1 - Красное, 2 - Черное):\n> ";
                    int colorChoice;
                    std::cin >> colorChoice;
                    RouletteColor selectedColor = (colorChoice == 1) ? RouletteColor::Red : RouletteColor::Black;
                    currentBet = std::make_unique<ColorBet>(Money(betAmount), selectedColor);
                    betDescription = "Цвет: " + std::string(colorChoice == 1 ? "Красное" : "Черное"); 
                } 
                else {
                    std::cout << "Число (0-36):\n> ";
                    int numberChoice;
                    std::cin >> numberChoice;
                    currentBet = std::make_unique<NumberBet>(Money(betAmount), numberChoice);
                    betDescription = "Число " + std::to_string(numberChoice);
                }

                RouletteNumber winningNumber = session.playRound(*currentBet);
                std::cout << "\n>>> ВЫПАЛО: " << winningNumber.getValue() << " (" << winningNumber.getColorName() << ") <<<\n";

                Money actualPayout(0);
                if (currentBet->isWinning(winningNumber)) {
                    actualPayout = currentBet->calculatePayout();
                    std::cout << "ПОБЕДА! Выигрыш: " << actualPayout.getAmount() << "\n";
                } else {
                    std::cout << "Проигрыш.\n";
                }

                journal.addRecord(betDescription, winningNumber, actualPayout, player.getBalance(), bank.getBalance());
            } catch (const std::exception& e) {
                std::cerr << "[ОШИБКА] " << e.what() << "\n";
                clearInput();
            }
        }
    }

    try {
        journal.saveToFile("casino_journal.csv");
        std::cout << "\n[УСПЕХ] История игры сохранена в 'casino_journal.csv'.\n";
    } catch (const std::exception& e) {
        std::cerr << "\n[ОШИБКА] " << e.what() << "\n";
    }

    return 0;
}
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

void clearInput() {
    std::cin.clear();
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}

int main() {
    std::cout << "==================================================\n";
    std::cout << "       СИМУЛЯТОР ЕВРОПЕЙСКОЙ РУЛЕТКИ (v1.0)       \n";
    std::cout << "==================================================\n\n";

    // --- ИНТЕРАКТИВНАЯ НАСТРОЙКА ---
    std::cout << "Введите ваше имя:\n> ";
    std::string playerName;
    std::cin >> playerName;

    std::cout << "Сколько фишек вы хотите купить на старте, " << playerName << "?\n> ";
    int initialBalance;
    while (!(std::cin >> initialBalance) || initialBalance <= 0) {
        clearInput();
        std::cout << "Ошибка! Введите положительное число:\n> ";
    }

    std::cout << "Введите начальное значение генератора (seed) для воспроизводимости раундов:\n";
    std::cout << "(Ввод одного и того же числа даст идентичную последовательность выпадений)\n> ";
    unsigned int seed;
    while (!(std::cin >> seed)) {
        clearInput();
        std::cout << "Ошибка! Введите целое положительное число:\n> ";
    }
    std::cout << "\nНастройка завершена. Загрузка стола...\n\n";

    Player player(playerName, Money(initialBalance));
    CasinoBank bank(Money(1000000)); 
    Table table(Money(100), Money(10000)); 
    RouletteWheel wheel(seed);
    GameSession session(player, bank, table, wheel);

    std::cout << "=== Добро пожаловать за игровой стол ===\n";
    std::cout << "Лимиты стола: от " << table.getMinBet().getAmount() 
              << " до " << table.getMaxBet().getAmount() << "\n\n";

    while (true) {
        std::cout << "--------------------------------------------------\n";
        std::cout << "[Баланс] " << player.getName() << ": " << player.getBalance().getAmount() << " | "
                  << "Касса: " << bank.getBalance().getAmount() << "\n";
        
        if (player.getBalance().getAmount() == 0) {
            std::cout << "Ваш баланс равен нулю. Игра окончена!\n";
            break;
        }

        std::cout << "Выберите действие:\n1. Поставить на цвет (1:1)\n2. Поставить на число (35:1)\n0. Забрать фишки и уйти\n> ";
        
        int choice;
        if (!(std::cin >> choice)) {
            clearInput();
            std::cout << "Ошибка ввода. Введите число 0, 1 или 2.\n";
            continue;
        }

        if (choice == 0) {
            std::cout << "Спасибо за игру, " << player.getName() << "! Вы ушли с балансом: " << player.getBalance().getAmount() << "\n";
            break;
        }

        if (choice != 1 && choice != 2) {
            std::cout << "Неверный выбор. Повторите.\n";
            continue;
        }

        std::cout << "Введите сумму ставки:\n> ";
        int betAmount;
        if (!(std::cin >> betAmount)) {
            clearInput();
            std::cout << "Ошибка ввода суммы.\n";
            continue;
        }

        std::unique_ptr<Bet> currentBet;

        try {
            if (choice == 1) {
                std::cout << "Выберите цвет (1 - Красное, 2 - Черное):\n> ";
                int colorChoice;
                if (!(std::cin >> colorChoice) || (colorChoice != 1 && colorChoice != 2)) {
                    clearInput();
                    throw std::invalid_argument("Неверный выбор цвета.");
                }
                
                RouletteColor selectedColor = (colorChoice == 1) ? RouletteColor::Red : RouletteColor::Black;
                currentBet = std::make_unique<ColorBet>(Money(betAmount), selectedColor);
            } 
            else if (choice == 2) {
                std::cout << "Введите число (0-36):\n> ";
                int numberChoice;
                if (!(std::cin >> numberChoice)) {
                    clearInput();
                    throw std::invalid_argument("Неверный ввод числа.");
                }
                currentBet = std::make_unique<NumberBet>(Money(betAmount), numberChoice);
            }

            RouletteNumber winningNumber = session.playRound(*currentBet);

            std::cout << "\n>>> РУЛЕТКА КРУТИТСЯ... Выпало: " 
                      << winningNumber.getValue() << " (" << winningNumber.getColorName() << ") <<<\n";

            if (currentBet->isWinning(winningNumber)) {
                std::cout << "!!! ПОБЕДА !!! Вы выиграли " << currentBet->calculatePayout().getAmount() << "\n";
            } else {
                std::cout << "К сожалению, ставка не сыграла.\n";
            }

        } catch (const std::exception& e) {
            std::cerr << "[ОШИБКА] " << e.what() << "\n";
            clearInput();
        }
    }

    return 0;
}
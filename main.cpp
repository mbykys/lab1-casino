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

void clearInput() {
    std::cin.clear();
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}

int main() {
    std::cout << "==================================================\n";
    std::cout << "       СИМУЛЯТОР ЕВРОПЕЙСКОЙ РУЛЕТКИ (v1.0)       \n";
    std::cout << "==================================================\n\n";

    std::cout << "Введите ваше имя:\n> ";
    std::string playerName;
    std::cin >> playerName;

    std::cout << "Сколько фишек вы хотите купить на старте, " << playerName << "?\n> ";
    int initialBalance;
    while (!(std::cin >> initialBalance) || initialBalance <= 0) {
        clearInput();
        std::cout << "Ошибка! Введите положительное число:\n> ";
    }

    std::cout << "Введите начальное значение генератора (seed):\n> ";
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
    
    GameJournal journal; 

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
            std::cout << "Ошибка ввода.\n";
            continue;
        }

        if (choice == 0) {
            std::cout << "Спасибо за игру! Вы ушли с балансом: " << player.getBalance().getAmount() << "\n";
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
        std::string betDescription; 

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
                
                betDescription = "Цвет: " + std::string(colorChoice == 1 ? "Красное" : "Черное"); 
            } 
            else if (choice == 2) {
                std::cout << "Введите число (0-36):\n> ";
                int numberChoice;
                if (!(std::cin >> numberChoice)) {
                    clearInput();
                    throw std::invalid_argument("Неверный ввод числа.");
                }
                currentBet = std::make_unique<NumberBet>(Money(betAmount), numberChoice);
                
                betDescription = "Число " + std::to_string(numberChoice);
            }

            RouletteNumber winningNumber = session.playRound(*currentBet);

            std::cout << "\n>>> РУЛЕТКА КРУТИТСЯ... Выпало: " 
                      << winningNumber.getValue() << " (" << winningNumber.getColorName() << ") <<<\n";

            Money actualPayout(0);
            if (currentBet->isWinning(winningNumber)) {
                actualPayout = currentBet->calculatePayout();
                std::cout << "!!! ПОБЕДА !!! Вы выиграли " << actualPayout.getAmount() << "\n";
            } else {
                std::cout << "К сожалению, ставка не сыграла.\n";
            }

            journal.addRecord(betDescription, winningNumber, actualPayout, player.getBalance(), bank.getBalance());

        } catch (const std::exception& e) {
            std::cerr << "[ОШИБКА] " << e.what() << "\n";
            clearInput();
        }
    }

    try {
        journal.saveToFile("casino_journal.csv");
        std::cout << "\n[УСПЕХ] История игры сохранена в файл 'casino_journal.csv'.\n";
    } catch (const std::exception& e) {
        std::cerr << "\n[ОШИБКА СОХРАНЕНИЯ] " << e.what() << "\n";
    }

    return 0;
}
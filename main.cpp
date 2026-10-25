#include <iostream>
#include "Money.hpp"

int main() {
    try {
        Money playerBalance(1000); 
        std::cout << "Симулятор казино запущен!" << std::endl;
        std::cout << "Баланс игрока: " << playerBalance.getAmount() << std::endl;
    } catch (const std::exception& e) {
        std::cerr << "Критическая ошибка: " << e.what() << std::endl;
        return 1;
    }
    return 0;
}
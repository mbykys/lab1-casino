#include "Money.hpp"

Money::Money(int initial_amount) {
    if (initial_amount < 0) {
        throw std::invalid_argument("Баланс не может быть отрицательным");
    }
    amount = initial_amount;
}

int Money::getAmount() const {
    return amount;
}

void Money::add(const Money& other) {
    amount += other.amount;
}

void Money::subtract(const Money& other) {
    if (amount < other.amount) {
        throw std::invalid_argument("Недостаточно средств");
    }
    amount -= other.amount;
}
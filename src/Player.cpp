#include "Player.hpp"

Player::Player(const std::string& playerName, const Money& initialBalance) 
    : name(playerName), balance(initialBalance) {}

std::string Player::getName() const {
    return name;
}

Money Player::getBalance() const {
    return balance;
}

void Player::withdraw(const Money& amount) {
    balance.subtract(amount);
}

void Player::deposit(const Money& amount) {
    balance.add(amount);
}
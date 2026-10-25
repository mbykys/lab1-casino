#pragma once
#include <string>
#include "Money.hpp"

class Player {
private:
    std::string name;
    Money balance;

public:
    Player(const std::string& playerName, const Money& initialBalance);

    std::string getName() const;
    Money getBalance() const;

    void withdraw(const Money& amount);

    void deposit(const Money& amount);
};
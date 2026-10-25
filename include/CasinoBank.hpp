#pragma once
#include "Money.hpp"

class CasinoBank {
private:
    Money balance;

public:
    explicit CasinoBank(const Money& initialBalance);

    Money getBalance() const;

    void withdraw(const Money& amount);
    void deposit(const Money& amount);
};
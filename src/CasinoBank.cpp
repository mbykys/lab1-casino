#include "CasinoBank.hpp"

CasinoBank::CasinoBank(const Money& initialBalance) : balance(initialBalance) {}

Money CasinoBank::getBalance() const {
    return balance;
}

void CasinoBank::withdraw(const Money& amount) {
    balance.subtract(amount);
}

void CasinoBank::deposit(const Money& amount) {
    balance.add(amount);
}
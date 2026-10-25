#include <gtest/gtest.h>
#include "CasinoBank.hpp"

TEST(CasinoBankTest, Initialization) {
    CasinoBank bank(Money(10000));
    EXPECT_EQ(bank.getBalance().getAmount(), 10000);
}

TEST(CasinoBankTest, DepositIncreasesBalance) {
    CasinoBank bank(Money(5000));
    bank.deposit(Money(1500));
    EXPECT_EQ(bank.getBalance().getAmount(), 6500);
}

TEST(CasinoBankTest, WithdrawDecreasesBalance) {
    CasinoBank bank(Money(5000));
    bank.withdraw(Money(1500));
    EXPECT_EQ(bank.getBalance().getAmount(), 3500);
}

TEST(CasinoBankTest, WithdrawThrowsWhenInsufficientFunds) {
    CasinoBank bank(Money(1000));
    EXPECT_THROW(bank.withdraw(Money(5000)), std::invalid_argument);
}
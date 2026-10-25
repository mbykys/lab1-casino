#include <gtest/gtest.h>
#include "Player.hpp"

TEST(PlayerTest, Initialization) {
    Player p("Alice", Money(1000));
    EXPECT_EQ(p.getName(), "Alice");
    EXPECT_EQ(p.getBalance().getAmount(), 1000);
}

TEST(PlayerTest, DepositIncreasesBalance) {
    Player p("Bob", Money(500));
    p.deposit(Money(200));
    EXPECT_EQ(p.getBalance().getAmount(), 700);
}

TEST(PlayerTest, WithdrawDecreasesBalance) {
    Player p("Charlie", Money(500));
    p.withdraw(Money(200));
    EXPECT_EQ(p.getBalance().getAmount(), 300);
}

TEST(PlayerTest, WithdrawThrowsWhenInsufficientFunds) {
    Player p("Dave", Money(100));
    EXPECT_THROW(p.withdraw(Money(200)), std::invalid_argument);
}
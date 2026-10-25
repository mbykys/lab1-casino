#include <gtest/gtest.h>
#include "Money.hpp"

TEST(MoneyTest, InitialBalanceIsCorrect) {
    Money m(100);
    EXPECT_EQ(m.getAmount(), 100);
}

TEST(MoneyTest, CannotCreateNegativeBalance) {
    EXPECT_THROW(Money(-50), std::invalid_argument);
}

TEST(MoneyTest, SubtractionThrowsWhenInsufficientFunds) {
    Money m(50);
    Money bet(100);
    EXPECT_THROW(m.subtract(bet), std::invalid_argument);
}
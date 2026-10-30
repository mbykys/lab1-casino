#include <gtest/gtest.h>
#include "Table.hpp"

TEST(TableTest, ValidInitialization) {
    Table t(Money(100), Money(1000));
    EXPECT_EQ(t.getMinBet().getAmount(), 100);
    EXPECT_EQ(t.getMaxBet().getAmount(), 1000);
}

TEST(TableTest, InvalidInitializationThrows) {
    EXPECT_THROW(Table(Money(1000), Money(100)), std::invalid_argument);
}

TEST(TableTest, BetWithinLimitsIsValid) {
    Table t(Money(100), Money(1000));
    
    EXPECT_NO_THROW(t.validateBet(Money(500)));
    EXPECT_NO_THROW(t.validateBet(Money(100)));
    EXPECT_NO_THROW(t.validateBet(Money(1000)));
}

TEST(TableTest, BetBelowMinThrows) {
    Table t(Money(100), Money(1000));
    EXPECT_THROW(t.validateBet(Money(50)), std::invalid_argument);
}

TEST(TableTest, BetAboveMaxThrows) {
    Table t(Money(100), Money(1000));
    EXPECT_THROW(t.validateBet(Money(1500)), std::invalid_argument);
}
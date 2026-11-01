#include <gtest/gtest.h>
#include "Bet.hpp"

TEST(ColorBetTest, WinningCondition) {
    ColorBet bet(Money(100), RouletteColor::Red);
    
    EXPECT_TRUE(bet.isWinning(RouletteNumber(1)));
    
    EXPECT_FALSE(bet.isWinning(RouletteNumber(2)));
    EXPECT_FALSE(bet.isWinning(RouletteNumber(0)));
}

TEST(ColorBetTest, PayoutIsCorrect) {
    ColorBet bet(Money(100), RouletteColor::Black);
    EXPECT_EQ(bet.calculatePayout().getAmount(), 200);
}

TEST(ColorBetTest, CannotBetOnGreenColor) {
    EXPECT_THROW(ColorBet(Money(100), RouletteColor::Green), std::invalid_argument);
}

TEST(NumberBetTest, WinningCondition) {
    NumberBet bet(Money(50), 17);
    
    EXPECT_TRUE(bet.isWinning(RouletteNumber(17)));
    EXPECT_FALSE(bet.isWinning(RouletteNumber(18)));
}

TEST(NumberBetTest, PayoutIsCorrect) {
    NumberBet bet(Money(10), 5);
    EXPECT_EQ(bet.calculatePayout().getAmount(), 360);
}

TEST(NumberBetTest, OutOfBoundsNumberThrows) {
    EXPECT_THROW(NumberBet(Money(100), -5), std::invalid_argument);
    EXPECT_THROW(NumberBet(Money(100), 37), std::invalid_argument);
}
#include <gtest/gtest.h>
#include "RouletteNumber.hpp"

TEST(RouletteNumberTest, ValidNumbersAreAccepted) {
    EXPECT_NO_THROW(RouletteNumber(0));
    EXPECT_NO_THROW(RouletteNumber(36));
}

TEST(RouletteNumberTest, InvalidNumbersThrowException) {
    EXPECT_THROW(RouletteNumber(-1), std::invalid_argument);
    EXPECT_THROW(RouletteNumber(37), std::invalid_argument);
}

TEST(RouletteNumberTest, ZeroIsGreen) {
    RouletteNumber zero(0);
    EXPECT_EQ(zero.getColor(), RouletteColor::Green);
}

TEST(RouletteNumberTest, ColorDistributionIsCorrect) {
    EXPECT_EQ(RouletteNumber(1).getColor(), RouletteColor::Red);
    EXPECT_EQ(RouletteNumber(2).getColor(), RouletteColor::Black);
    
    EXPECT_EQ(RouletteNumber(11).getColor(), RouletteColor::Black);
    EXPECT_EQ(RouletteNumber(12).getColor(), RouletteColor::Red);
}
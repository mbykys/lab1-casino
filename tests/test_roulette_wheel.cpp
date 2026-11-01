#include <gtest/gtest.h>
#include "RouletteWheel.hpp"

TEST(RouletteWheelTest, ValuesAreWithinBounds) {
    RouletteWheel wheel(42); 
    
    for (int i = 0; i < 1000; ++i) {
        RouletteNumber result = wheel.spin();
        EXPECT_GE(result.getValue(), 0); 
        EXPECT_LE(result.getValue(), 36); 
    }
}

TEST(RouletteWheelTest, ReproducibilityWithSameSeed) {
    RouletteWheel wheel1(12345);
    RouletteWheel wheel2(12345);

    for (int i = 0; i < 10; ++i) {
        EXPECT_EQ(wheel1.spin().getValue(), wheel2.spin().getValue());
    }
}
#include <gtest/gtest.h>
#include "BotStrategy.hpp"

TEST(BotStrategyTest, MartingaleDoublesOnLoss) {
    Player dummyPlayer("Bot", Money(1000));
    Table dummyTable(Money(10), Money(1000));
    
    MartingaleStrategy strategy(Money(100), RouletteColor::Red);
    
    auto bet1 = strategy.generateBet(dummyTable, dummyPlayer);
    EXPECT_EQ(bet1->getAmount().getAmount(), 100);
    
    strategy.updateFeedback(false);
    
    auto bet2 = strategy.generateBet(dummyTable, dummyPlayer);
    EXPECT_EQ(bet2->getAmount().getAmount(), 200);
    
    strategy.updateFeedback(true);
    
    auto bet3 = strategy.generateBet(dummyTable, dummyPlayer);
    EXPECT_EQ(bet3->getAmount().getAmount(), 100);
}
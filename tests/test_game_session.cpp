#include <gtest/gtest.h>
#include "GameSession.hpp"

TEST(GameSessionTest, RoundExecutionMathIsCorrect) {
    Player p("TestPlayer", Money(1000));
    CasinoBank b(Money(10000));
    Table t(Money(10), Money(1000));
    RouletteWheel w(42);
    GameSession session(p, b, t, w);

    ColorBet bet(Money(100), RouletteColor::Red);
    
    RouletteNumber result = session.playRound(bet);

    if (result.getColor() == RouletteColor::Red) {
        EXPECT_EQ(p.getBalance().getAmount(), 1100);
        EXPECT_EQ(b.getBalance().getAmount(), 9900);
    } else {
        EXPECT_EQ(p.getBalance().getAmount(), 900);
        EXPECT_EQ(b.getBalance().getAmount(), 10100);
    }
}

TEST(GameSessionTest, CannotPlayIfCasinoIsTooPoor) {
    Player p("TestPlayer", Money(5000));
    CasinoBank b(Money(1000)); 
    Table t(Money(10), Money(5000));
    RouletteWheel w(42);
    GameSession session(p, b, t, w);

    NumberBet bet(Money(1000), 17);
    
    EXPECT_THROW(session.playRound(bet), std::runtime_error);
    
    EXPECT_EQ(p.getBalance().getAmount(), 5000);
}
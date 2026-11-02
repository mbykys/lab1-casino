#pragma once
#include "GameSession.hpp"
#include "BotStrategy.hpp"
#include "GameJournal.hpp"
#include "CasinoBank.hpp"

class BotEngine {
private:
    GameSession& session;
    Player& player;
    const Table& table;
    CasinoBank& bank;
    BotStrategy& strategy;
    GameJournal& journal;
    
    int maxSpins;
    Money winTarget; 
    Money lossLimit; 

public:
    BotEngine(GameSession& s, Player& p, const Table& t, CasinoBank& b, BotStrategy& strat, GameJournal& j,
              int spins, const Money& target, const Money& limit);

    void run();
};
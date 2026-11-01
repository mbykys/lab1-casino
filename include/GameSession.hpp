#pragma once
#include "Player.hpp"
#include "CasinoBank.hpp"
#include "Table.hpp"
#include "RouletteWheel.hpp"
#include "Bet.hpp"

class GameSession {
private:
    Player& player;
    CasinoBank& bank;
    const Table& table; 
    RouletteWheel& wheel;

public:
    GameSession(Player& p, CasinoBank& b, const Table& t, RouletteWheel& w);

    RouletteNumber playRound(const Bet& bet);
};
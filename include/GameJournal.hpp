#pragma once
#include <string>
#include <vector>
#include "Money.hpp"
#include "RouletteNumber.hpp"

struct RoundRecord {
    std::string betInfo;
    int outcomeNumber;
    std::string outcomeColor;
    int payoutAmount;
    int playerBalance;
    int bankBalance;
};

class GameJournal {
private:
    std::vector<RoundRecord> records;

public:
    void addRecord(const std::string& betInfo, const RouletteNumber& outcome, 
                   const Money& payout, const Money& playerBalance, const Money& bankBalance);

    void saveToFile(const std::string& filename) const;

    void loadFromFile(const std::string& filename);

    const std::vector<RoundRecord>& getRecords() const;
};
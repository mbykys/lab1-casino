#include "GameJournal.hpp"
#include <fstream>
#include <sstream>
#include <stdexcept>

void GameJournal::addRecord(const std::string& betInfo, const RouletteNumber& outcome, 
                            const Money& payout, const Money& playerBalance, const Money& bankBalance) {
    RoundRecord record{
        betInfo,
        outcome.getValue(),
        outcome.getColorName(),
        payout.getAmount(),
        playerBalance.getAmount(),
        bankBalance.getAmount()
    };
    records.push_back(record);
}

void GameJournal::saveToFile(const std::string& filename) const {
    std::ofstream file(filename);
    if (!file.is_open()) {
        throw std::runtime_error("Не удалось открыть файл для сохранения журнала.");
    }

    file << "Ставка,Выпало число,Цвет,Выплата,Баланс Игрока,Баланс Кассы\n";

    for (const auto& record : records) {
        file << record.betInfo << ","
             << record.outcomeNumber << ","
             << record.outcomeColor << ","
             << record.payoutAmount << ","
             << record.playerBalance << ","
             << record.bankBalance << "\n";
    }
}

void GameJournal::loadFromFile(const std::string& filename) {
    std::ifstream file(filename);
    if (!file.is_open()) {
        throw std::runtime_error("Не удалось открыть файл для чтения журнала.");
    }

    records.clear(); 
    std::string line;
    
    std::getline(file, line); 

    while (std::getline(file, line)) {
        std::stringstream ss(line);
        std::string token;
        RoundRecord record;

        std::getline(ss, record.betInfo, ',');
        
        std::getline(ss, token, ',');
        record.outcomeNumber = std::stoi(token); 
        
        std::getline(ss, record.outcomeColor, ',');
        
        std::getline(ss, token, ',');
        record.payoutAmount = std::stoi(token);
        
        std::getline(ss, token, ',');
        record.playerBalance = std::stoi(token);
        
        std::getline(ss, token, ',');
        record.bankBalance = std::stoi(token);

        records.push_back(record);
    }
}

const std::vector<RoundRecord>& GameJournal::getRecords() const {
    return records;
}
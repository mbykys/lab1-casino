#pragma once
#include <stdexcept>

class Money {
private:
    int amount;

public:
    explicit Money(int initial_amount = 0);
    
    int getAmount() const;
    void add(const Money& other);
    void subtract(const Money& other);
};
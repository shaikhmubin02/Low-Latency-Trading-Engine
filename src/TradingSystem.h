#ifndef TRADINGSYSTEM_H
#define TRADINGSYSTEM_H

#include <iostream>
#include <fstream>
#include <vector>
#include <chrono>
#include <iomanip>

using namespace std;

struct Order {
    int orderId;
    string symbol;
    double price;
    int quantity;
    char side; // 'B' for Buy, 'S' for Sell
    chrono::system_clock::time_point timestamp;

    Order(int id, const string& sym, double pr, int qty, char s)
        : orderId(id), symbol(sym), price(pr), quantity(qty), side(s), timestamp(chrono::system_clock::now()) {}
};

class TradingSystem {
private:
    vector<Order> orders;
    ofstream logFile;

public:
    TradingSystem();
    ~TradingSystem();

    void placeOrder(const Order& order);
    void executeTrade(const Order& order);
    void generateDailyReport() const;
};

#endif /* TRADINGSYSTEM_H */

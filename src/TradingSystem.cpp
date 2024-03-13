#include "../includes/TradingSystem.h"

TradingSystem::TradingSystem() {
    logFile.open("trading_log.txt", ios::out | ios::app);
    if (!logFile.is_open()) {
        cerr << "Error: Failed to open log file." << endl;
    }
}

TradingSystem::~TradingSystem() {
    if (logFile.is_open()) {
        logFile.close();
    }
}

void TradingSystem::placeOrder(const Order& order) {
    orders.push_back(order);
    // Log order
    auto time = chrono::system_clock::to_time_t(order.timestamp);
    logFile << "[" << put_time(localtime(&time), "%Y-%m-%d %H:%M:%S") << "] Order Placed: "
            << "OrderID: " << order.orderId << ", Symbol: " << order.symbol << ", Price: " << order.price
            << ", Quantity: " << order.quantity << ", Side: " << order.side << endl;
    
}

void TradingSystem::executeTrade(const Order& order) {
    
}

void TradingSystem::generateDailyReport() const {

    // Generate daily report based on logged data
    cout << "Generating daily report..." << endl;
    
}

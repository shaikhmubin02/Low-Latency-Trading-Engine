#include <iostream>
#include "TradingSystem.h"

using namespace std;

int main() {
    TradingSystem tradingSystem;

    // Simulate order placement and trade execution 
    Order order1(1, "AAPL", 150.0, 100, 'B');
    tradingSystem.placeOrder(order1);

    Order order2(2, "GOOGL", 160.0, 75, 'S');
    tradingSystem.placeOrder(order2);

    tradingSystem.generateDailyReport();

    return 0;
}

// g++ -c TradingSystem.cpp -o TradingSystem.o  # Compile TradingSystem.cpp into object file
// g++ main.cpp TradingSystem.o -o trading_app   # Compile main.cpp and link with TradingSystem.o to create executable
// ./trading_app                                 # Run the compiled executable


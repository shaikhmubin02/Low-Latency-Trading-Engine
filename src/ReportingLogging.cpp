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
    chrono::system_clock::time_point timestamp;  // Changed to system_clock

    Order(int id, const string& sym, double pr, int qty, char s)
        : orderId(id), symbol(sym), price(pr), quantity(qty), side(s), timestamp(chrono::system_clock::now()) {}
};

class TradingSystem {
private:
    vector<Order> orders;
    ofstream logFile;

public:
    TradingSystem() {
        logFile.open("trading_log.txt", ios::out | ios::app);
        if (!logFile.is_open()) {
            cerr << "Error: Failed to open log file." << endl;
        }
    }

    ~TradingSystem() {
        if (logFile.is_open()) {
            logFile.close();
        }
    }

    void placeOrder(const Order& order) {
        orders.push_back(order);
        logOrder("Order Placed", order);
        // Implement order placement logic here
    }

    void executeTrade(const Order& order) {
        logOrder("Trade Executed", order);
        // Implement trade execution logic here
    }

    void logOrder(const string& eventType, const Order& order) {
        auto time = chrono::system_clock::to_time_t(order.timestamp);  // Changed to system_clock
        logFile << "[" << put_time(localtime(&time), "%Y-%m-%d %H:%M:%S") << "] " << eventType << ": "
                << "OrderID: " << order.orderId << ", Symbol: " << order.symbol << ", Price: " << order.price
                << ", Quantity: " << order.quantity << ", Side: " << order.side << endl;
    }

    void generateDailyReport() {
        ofstream reportFile("daily_report.txt");
        if (reportFile.is_open()) {
            // Generate daily report based on logged data
            reportFile << "Daily Trading Report\n\n";
            reportFile << "Timestamp,Event,OrderID,Symbol,Price,Quantity,Side\n";
            for (const auto& order : orders) {
                auto time = chrono::system_clock::to_time_t(order.timestamp);  // Changed to system_clock
                reportFile << put_time(localtime(&time), "%Y-%m-%d %H:%M:%S") << ","
                           << "Order Placed," << order.orderId << "," << order.symbol << ","
                           << order.price << "," << order.quantity << "," << order.side << "\n";
            }
            reportFile.close();
            cout << "Daily report generated successfully." << endl;
        } else {
            cerr << "Error: Failed to create daily report file." << endl;
        }
    }
};

int main() {
    TradingSystem tradingSystem;

    // Simulate order placement and trade execution (replace with actual trading logic)
    Order order1(1, "AAPL", 150.0, 100, 'B');
    tradingSystem.placeOrder(order1);

    Order order2(2, "GOOGL", 160.0, 75, 'S');
    tradingSystem.placeOrder(order2);

    Order tradeOrder(1, "AAPL", 150.0, 100, 'B');
    tradingSystem.executeTrade(tradeOrder);

    // Generate daily report
    tradingSystem.generateDailyReport();

    return 0;
}

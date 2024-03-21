#include <iostream>
#include <vector>
#include <algorithm>
#include <chrono>
#include <random>
#include <ctime>

using namespace std;

enum class OrderSide { Buy, Sell };

struct Order {
    int orderId;
    string symbol;
    double price;
    int quantity;
    OrderSide side;

    Order(int id, const string& sym, double pr, int qty, OrderSide sd) : orderId(id), symbol(sym), price(pr), quantity(qty), side(sd) {}
};

class RiskManagement {
private:
    double maxPositionSize;
    double maxInventoryExposure;
    double maxOrderSize;
    double maxLossLimit;
    mt19937 rng; // Random number generator for simulating risk breaches

public:
    RiskManagement(double posSize, double invExposure, double ordSize, double lossLimit)
        : maxPositionSize(posSize), maxInventoryExposure(invExposure),
          maxOrderSize(ordSize), maxLossLimit(lossLimit), rng(static_cast<unsigned int>(chrono::steady_clock::now().time_since_epoch().count())) {}

    bool checkRiskLimits(const Order& order) {
        // Simulate dynamic risk limits based on market conditions
        updateDynamicLimits();

        // Perform risk checks
        if (order.quantity > maxOrderSize) {
            cout << "Risk Limit Breach: Max Order Size Exceeded" << endl;
            return false;
        }
        // Implement other risk checks based on your risk management rules

        return true;
    }

    void updateDynamicLimits() {
        // Simulate dynamic updates to risk limits based on market conditions
        uniform_real_distribution<double> dist(-0.05, 0.05); // Simulate 5% change
        double change = dist(rng);

        maxPositionSize *= (1.0 + change);
        maxInventoryExposure *= (1.0 + change);
        maxOrderSize *= (1.0 + change);
        maxLossLimit *= (1.0 + change);

        cout << "Dynamic Risk Limits Updated:" << endl;
        cout << "Max Position Size: " << maxPositionSize << endl;
        cout << "Max Inventory Exposure: " << maxInventoryExposure << endl;
        cout << "Max Order Size: " << maxOrderSize << endl;
        cout << "Max Loss Limit: " << maxLossLimit << endl;
    }

    void simulateRiskBreaches() {
        // Simulate risk breaches for demonstration purposes
        uniform_real_distribution<double> dist(0.0, 1.0);
        double riskProb = dist(rng);

        if (riskProb < 0.1) { // 10% chance of risk breach
            cout << "Simulating Risk Breach: Position Risk Exceeded" << endl;
            // Trigger appropriate actions such as order rejection, position liquidation, etc.
        }
    }
};

class OrderExecutionEngine {
private:
    vector<Order> orders;
    int nextOrderId;
    RiskManagement riskManager;

public:
    OrderExecutionEngine(double posSize, double invExposure, double ordSize, double lossLimit)
        : nextOrderId(1), riskManager(posSize, invExposure, ordSize, lossLimit) {}

    void addOrder(const string& symbol, double price, int quantity, OrderSide side) {
        Order newOrder(nextOrderId++, symbol, price, quantity, side);
        if (riskManager.checkRiskLimits(newOrder)) {
            orders.push_back(newOrder);
            cout << "Order Added: Symbol: " << newOrder.symbol << ", Price: " << newOrder.price
                 << ", Quantity: " << newOrder.quantity << ", Side: " << (newOrder.side == OrderSide::Buy ? "Buy" : "Sell") << endl;
        } else {
            cout << "Order Rejected: Risk Limits Exceeded" << endl;
        }

        riskManager.simulateRiskBreaches(); // Simulate risk breaches periodically
    }

    void printOrders() const {
        for (const auto& order : orders) {
            cout << "Order ID: " << order.orderId << ", Symbol: " << order.symbol
                 << ", Quantity: " << order.quantity << ", Price: " << order.price << endl;
        }
    }
};

int main() {
    OrderExecutionEngine executionEngine(10000.0, 500000.0, 1000.0, 100000.0); // Initial risk limits

    // Simulate orders with risk checks
    executionEngine.addOrder("AAPL", 150.0, 100, OrderSide::Buy);
    executionEngine.addOrder("GOOGL", 160.0, 1200, OrderSide::Sell);
    executionEngine.addOrder("MSFT", 140.0, 900, OrderSide::Buy);
    executionEngine.addOrder("AMZN", 1800.0, 800, OrderSide::Sell);

    // Print orders
    executionEngine.printOrders();

    return 0;
}

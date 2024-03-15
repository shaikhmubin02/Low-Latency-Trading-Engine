#include <iostream>
#include <vector>
#include <random>
#include <chrono>
#include <algorithm>

using namespace std;

// Define an enum for order side
enum class OrderSide { Buy, Sell };

// Define a structure to represent an order
struct Order {
    string symbol;
    double price;
    int quantity;
    OrderSide side;

    Order(const string& sym, double pr, int qty, OrderSide sd) : symbol(sym), price(pr), quantity(qty), side(sd) {}
};

// Market-Making Strategy Class
class MarketMaker {
private:
    double midPrice; // Current mid price
    double spread; // Desired spread (percentage)
    double minPrice; // Minimum price allowed
    double maxPrice; // Maximum price allowed
    mt19937 rng; // Mersenne Twister random number generator

public:
    MarketMaker(double mid, double sprd, double minPr, double maxPr) :
        midPrice(mid), spread(sprd), minPrice(minPr), maxPrice(maxPr),
        rng(static_cast<unsigned int>(chrono::steady_clock::now().time_since_epoch().count())) {}

    // Update the mid price
    void updateMidPrice(double newMidPrice) {
        midPrice = newMidPrice;
    }

    // Generate bid and ask orders based on the market conditions
    vector<Order> generateOrders(int inventory) {
        double buyPrice = midPrice * (1 - spread); // Buy price based on spread
        double sellPrice = midPrice * (1 + spread); // Sell price based on spread

        // Adjust prices based on inventory (example linear model)
        double spreadFactor = 0.001 * inventory;
        buyPrice -= spreadFactor; // Decrease buy price with increasing inventory
        sellPrice += spreadFactor; // Increase sell price with increasing inventory

        // Ensure prices are within the allowed range
        buyPrice = max(buyPrice, minPrice);
        sellPrice = min(sellPrice, maxPrice);

        // Generate random order quantities (example uniform distribution)
        uniform_int_distribution<int> qtyDist(10, 50);
        int buyQty = qtyDist(rng);
        int sellQty = qtyDist(rng);

        // Create bid and ask orders
        vector<Order> orders;
        orders.push_back(Order("AAPL", buyPrice, buyQty, OrderSide::Buy)); // Buy order
        orders.push_back(Order("AAPL", sellPrice, sellQty, OrderSide::Sell)); // Sell order

        return orders;
    }
};

int main() {
    MarketMaker marketMaker(100.0, 0.01, 95.0, 105.0); // Initialize market maker
    int initialInventory = 0;

    // Simulate market updates and order generation
    for (int i = 0; i < 10; ++i) {
        double newMidPrice = 100.0 + (i % 3 == 0 ? -0.5 : 0.5); // Simulate mid price changes
        marketMaker.updateMidPrice(newMidPrice);

        // Adjust inventory based on simulation (example linear model)
        initialInventory += (i % 2 == 0 ? 10 : -5);

        // Generate and display orders
        vector<Order> orders = marketMaker.generateOrders(initialInventory);
        cout << "Round " << i + 1 << " Orders:" << endl;
        for (const auto& order : orders) {
            cout << "Symbol: " << order.symbol << ", Price: " << order.price
                 << ", Quantity: " << order.quantity << ", Side: " << (order.side == OrderSide::Buy ? "Buy" : "Sell") << endl;
        }
        cout << "-----------------------------" << endl;
    }

    return 0;
}

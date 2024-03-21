#include <iostream>
#include <vector>
#include <algorithm>
#include <chrono>
#include <random>

using namespace std;

// Define an enum for order side
enum class OrderSide { Buy, Sell };

// Define a structure to represent an order
struct Order {
    int orderId;
    string symbol;
    double price;
    int quantity;
    OrderSide side;

    Order(int id, const string& sym, double pr, int qty, OrderSide sd) : orderId(id), symbol(sym), price(pr), quantity(qty), side(sd) {}
};

// Order Execution Engine Class
class OrderExecutionEngine {
private:
    vector<Order> buyOrders; // Buy orders in the order book
    vector<Order> sellOrders; // Sell orders in the order book
    int nextOrderId; // Next order ID
    double lastTradedPrice; // Last traded price (for tracking slippage)
    mt19937 rng; // Mersenne Twister random number generator

public:
    OrderExecutionEngine() : nextOrderId(1), lastTradedPrice(100.0), rng(static_cast<unsigned int>(chrono::steady_clock::now().time_since_epoch().count())) {}

    // Add a new order to the order book
    void addOrder(const string& symbol, double price, int quantity, OrderSide side) {
        Order newOrder(nextOrderId++, symbol, price, quantity, side);
        if (validateOrder(newOrder)) {
            if (side == OrderSide::Buy) {
                buyOrders.push_back(newOrder);
                prioritizeOrders(buyOrders);
            } else {
                sellOrders.push_back(newOrder);
                prioritizeOrders(sellOrders);
            }
            matchMarketOrders(); // Try to match new order immediately
        } else {
            cout << "Invalid order: Symbol: " << newOrder.symbol << ", Price: " << newOrder.price
                 << ", Quantity: " << newOrder.quantity << ", Side: " << (newOrder.side == OrderSide::Buy ? "Buy" : "Sell") << endl;
        }
    }

    // Validate an order (basic validation for demonstration)
    bool validateOrder(const Order& order) {
        return order.price > 0 && order.quantity > 0;
    }

    // Prioritize orders in the order book based on price and timestamp
    void prioritizeOrders(vector<Order>& orders) {
        sort(orders.begin(), orders.end(), [](const Order& a, const Order& b) {
            if (a.price == b.price) {
                return a.orderId < b.orderId; // Orders with same price are prioritized based on order ID
            }
            return a.price > b.price; // Sort buy orders by descending price, sell orders by ascending price
        });
    }

    // Match market orders against the order book and execute trades
    void matchMarketOrders() {
        while (!buyOrders.empty() && !sellOrders.empty()) {
            Order buyOrder = buyOrders.front();
            Order sellOrder = sellOrders.front();

            if (buyOrder.price >= sellOrder.price) {
                int tradeQuantity = min(buyOrder.quantity, sellOrder.quantity);
                executeTrade(buyOrder, sellOrder, tradeQuantity);

                // Update order quantities and remove filled orders
                buyOrder.quantity -= tradeQuantity;
                sellOrder.quantity -= tradeQuantity;

                if (buyOrder.quantity <= 0) {
                    buyOrders.erase(buyOrders.begin());
                }
                if (sellOrder.quantity <= 0) {
                    sellOrders.erase(sellOrders.begin());
                }
            } else {
                break; // No more matching orders
            }
        }
    }

    // Execute a trade between a buy order and a sell order
    void executeTrade(Order& buyOrder, Order& sellOrder, int tradeQuantity) {
        double tradePrice = (buyOrder.price + sellOrder.price) / 2.0; // Simplified average price
        lastTradedPrice = tradePrice;
        cout << "Trade Executed: Symbol: " << buyOrder.symbol << ", Quantity: " << tradeQuantity
             << ", Price: " << tradePrice << ", Side: Buy" << endl;
    }

    // Print the current state of the order book
    void printOrderBook() const {
        cout << "Buy Orders:" << endl;
        for (const auto& order : buyOrders) {
            cout << "Order ID: " << order.orderId << ", Symbol: " << order.symbol
                 << ", Quantity: " << order.quantity << ", Price: " << order.price << endl;
        }
        cout << "Sell Orders:" << endl;
        for (const auto& order : sellOrders) {
            cout << "Order ID: " << order.orderId << ", Symbol: " << order.symbol
                 << ", Quantity: " << order.quantity << ", Price: " << order.price << endl;
        }
        cout << "-----------------------------" << endl;
    }
};

int main() {
    OrderExecutionEngine executionEngine;

    // Add some sample orders to the order book
    executionEngine.addOrder("AAPL", 150.0, 100, OrderSide::Buy);
    executionEngine.addOrder("AAPL", 160.0, 50, OrderSide::Buy);
    executionEngine.addOrder("AAPL", 155.0, 75, OrderSide::Sell);
    executionEngine.addOrder("AAPL", 170.0, 125, OrderSide::Sell);

    // Print the initial state of the order book
    executionEngine.printOrderBook();

    // Add a new buy order (invalid order for demonstration)
    executionEngine.addOrder("AAPL", -5.0, 100, OrderSide::Buy);

    // Print the order book after adding an invalid order
    executionEngine.printOrderBook();

    return 0;
}

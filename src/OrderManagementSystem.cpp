#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

// an enum for order types
enum class OrderType { Market, Limit, Stop };

// an enum for order side
enum class OrderSide { Buy, Sell };

// structure to represent an order
struct Order {
    int orderId;
    string symbol;
    int quantity;
    double price;
    OrderType type;
    OrderSide side;
    bool isValid; // Flag to indicate order validity
    bool isFilled; // Flag to indicate if the order is fully filled

    Order(int id, const string& sym, int qty, double pr, OrderType t, OrderSide s)
        : orderId(id), symbol(sym), quantity(qty), price(pr), type(t), side(s), isValid(true), isFilled(false) {}

    // Check if the order matches another order for execution
    bool matches(const Order& other) const {
        if (symbol != other.symbol || side == other.side || isFilled || !other.isValid || (type == OrderType::Limit && price != other.price)) {
            return false; // Orders do not match
        }
        return true; // Orders match for execution
    }

    // Execute the order with a matching order
    void execute(const Order& matchingOrder) {
        if (type == OrderType::Market || (type == OrderType::Limit && price <= matchingOrder.price)) {
            isFilled = true; 
            cout << "Order ID " << orderId << " executed against Order ID " << matchingOrder.orderId << endl;
        }
    }
};

// structure to represent an order book for a symbol
struct OrderBook {
    vector<Order> orders;
    int nextOrderId;

    OrderBook() : nextOrderId(1) {}

    // Add a new order to the order book
    void addOrder(const string& symbol, int quantity, double price, OrderType type, OrderSide side) {
        Order newOrder(nextOrderId++, symbol, quantity, price, type, side);
        orders.push_back(newOrder);
        if (type == OrderType::Limit) {
            // Sort orders by price for limit orders
            sort(orders.begin(), orders.end(), [](const Order& a, const Order& b) {
                return a.price < b.price; // Sort buy orders by ascending price, sell orders by descending price
            });
        }
        matchAndExecuteOrders();
    }

    // Cancel an order from the order book
    void cancelOrder(int orderId) {
        auto it = find_if(orders.begin(), orders.end(), [orderId](const Order& order) {
            return order.orderId == orderId;
        });

        if (it != orders.end()) {
            it->isValid = false; // (cancelled)
            matchAndExecuteOrders(); // Match and execute remaining valid orders
            return;
        }

        cout << "Order ID " << orderId << " not found in the order book." << endl;
    }

    // Match and execute orders in the order book
    void matchAndExecuteOrders() {
        for (auto& order : orders) {
            if (!order.isValid || order.isFilled) continue; // Skip invalid or filled orders
            for (auto& other : orders) {
                if (&order == &other || !other.isValid || other.isFilled) continue; // Skip self, invalid, or filled orders
                if (order.matches(other)) {
                    order.execute(other); // Execute the order
                    other.isFilled = true; // Mark the matched order as filled
                }
            }
        }
        // Remove filled orders from the order book
        orders.erase(remove_if(orders.begin(), orders.end(), [](const Order& o) { return o.isFilled; }), orders.end());
    }

    // Print the current state of the order book
    void printOrderBook() const {
        cout << "Current Order Book:" << endl;
        for (const auto& order : orders) {
            cout << "Order ID: " << order.orderId << ", Symbol: " << order.symbol
                 << ", Quantity: " << order.quantity << ", Price: " << order.price
                 << ", Type: " << static_cast<int>(order.type) << ", Side: " << static_cast<int>(order.side)
                 << ", Valid: " << order.isValid << ", Filled: " << order.isFilled << endl;
        }
        cout << "-----------------------------" << endl;
    }
};

int main() {
    OrderBook orderBook;

    // Add some sample orders to the order book
    orderBook.addOrder("AAPL", 100, 150.0, OrderType::Limit, OrderSide::Buy);
    orderBook.addOrder("AAPL", 50, 160.0, OrderType::Limit, OrderSide::Buy);
    orderBook.addOrder("AAPL", 75, 155.0, OrderType::Limit, OrderSide::Sell);
    orderBook.addOrder("AAPL", 125, 170.0, OrderType::Limit, OrderSide::Sell);

    // Print the initial state of the order book
    orderBook.printOrderBook();

    // Cancel an order
    orderBook.cancelOrder(2);

    // Print the order book after cancellation and execution
    orderBook.printOrderBook();

    return 0;
}

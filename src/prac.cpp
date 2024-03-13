#include <iostream>
#include <vector>
#include <chrono>
#include <thread>
#include <random>
#include <algorithm>

using namespace std;

// Define a structure to represent a price update
struct PriceUpdate {
    string symbol;
    double price;
    int volume;
    string timestamp;
    string tradeType; // "Buy" or "Sell"
};

// Define structures for bid and ask orders in the order book
struct Order {
    double price;
    int volume;
};

struct OrderBook {
    vector<Order> bids;
    vector<Order> asks;
};

// Generate a random price update
PriceUpdate generateRandomPriceUpdate(const string& symbol, double basePrice, const string& currentTime) {
    static default_random_engine generator;
    static normal_distribution<double> distribution(0.0, 0.5); // mean = 0, stddev = 0.5

    double priceShift = distribution(generator);
    int volume = rand() % 1000 + 1; // Random volume between 1 and 1000

    PriceUpdate update;
    update.symbol = symbol;
    update.price = basePrice + priceShift;
    update.volume = volume;
    update.timestamp = currentTime;
    update.tradeType = (rand() % 2 == 0) ? "Buy" : "Sell"; // Randomly generate buy or sell trade type
    return update;
}

// Simulate order book changes based on incoming orders
void simulateOrderBook(OrderBook& orderBook, const PriceUpdate& update) {
    Order newOrder;
    newOrder.price = update.price;
    newOrder.volume = update.volume;

    if (update.tradeType == "Buy") {
        orderBook.bids.push_back(newOrder);
        sort(orderBook.bids.begin(), orderBook.bids.end(), [](const Order& a, const Order& b) {
            return a.price > b.price; // Sort bids in descending order
        });
    } else if (update.tradeType == "Sell") {
        orderBook.asks.push_back(newOrder);
        sort(orderBook.asks.begin(), orderBook.asks.end(), [](const Order& a, const Order& b) {
            return a.price < b.price; // Sort asks in ascending order
        });
    }
}

// Print the current state of the order book
void printOrderBook(const OrderBook& orderBook) {
    cout << "Current Order Book:" << endl;
    cout << "Bids:" << endl;
    for (const auto& bid : orderBook.bids) {
        cout << "Price: " << bid.price << ", Volume: " << bid.volume << endl;
    }
    cout << "Asks:" << endl;
    for (const auto& ask : orderBook.asks) {
        cout << "Price: " << ask.price << ", Volume: " << ask.volume << endl;
    }
    cout << "-----------------------------" << endl;
}

// Simulate market data feed for a stock
void simulateMarketDataFeed(const string& symbol, double initialPrice, int updatesCount) {
    double currentPrice = initialPrice;
    OrderBook orderBook;

    for (int i = 0; i < updatesCount; ++i) {
        // Get current time (for timestamp simulation)
        auto now = chrono::system_clock::now();
        auto currentTime = chrono::system_clock::to_time_t(now);

        // Generate a random price update
        PriceUpdate update = generateRandomPriceUpdate(symbol, currentPrice, ctime(&currentTime));

        // Update current price
        currentPrice = update.price;

        // Simulate order book changes based on the update
        simulateOrderBook(orderBook, update);

        // Print the simulated update
        cout << "Symbol: " << update.symbol << ", Timestamp: " << update.timestamp
             << ", Price: " << update.price << ", Volume: " << update.volume
             << ", Trade Type: " << update.tradeType << endl;

        // Print the current order book
        printOrderBook(orderBook);

        // Sleep for a short duration to simulate real-time updates
        this_thread::sleep_for(chrono::milliseconds(100));
    }
}

int main() {
    // Simulate market data feed for a stock with symbol "AAPL"
    string symbol = "AAPL";
    double initialPrice = 150.0;
    int updatesCount = 10;

    simulateMarketDataFeed(symbol, initialPrice, updatesCount);

    return 0;
}

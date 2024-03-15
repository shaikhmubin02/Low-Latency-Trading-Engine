#ifndef ORDERMANAGEMENTSYSTEM_H
#define ORDERMANAGEMENTSYSTEM_H

#include <string>

struct Order {
    int orderId;
    std::string symbol;
    double price;
    int quantity;
    char side; // 'B' for Buy, 'S' for Sell
};

class OrderManagementSystem {
public:
    void placeOrder(const Order& order);
    void modifyOrder(int orderId, double newPrice, int newQuantity);
    void cancelOrder(int orderId);
    
};

#endif /* ORDERMANAGEMENTSYSTEM_H */

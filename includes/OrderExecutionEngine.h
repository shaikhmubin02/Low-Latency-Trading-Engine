#ifndef ORDEREXECUTIONENGINE_H
#define ORDEREXECUTIONENGINE_H

#include "OrderManagementSystem.h"

class OrderExecutionEngine {
private:
    OrderManagementSystem& oms; // Reference to Order Management System

public:
    OrderExecutionEngine(OrderManagementSystem& omsRef);
    void processMarketOrder(const Order& order);
    // Add more functions or members as needed
};

#endif /* ORDEREXECUTIONENGINE_H */

#ifndef RISKMANAGEMENT_H
#define RISKMANAGEMENT_H

#include "OrderManagementSystem.h"

class RiskManagement {
private:
    OrderManagementSystem& oms; // Reference to Order Management System

public:
    RiskManagement(OrderManagementSystem& omsRef);
    void performRiskChecks(const Order& order);
    // Add more functions or members as needed
};

#endif /* RISKMANAGEMENT_H */

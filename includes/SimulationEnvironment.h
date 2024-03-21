#ifndef SIMULATIONENVIRONMENT_H
#define SIMULATIONENVIRONMENT_H

#include "MarketDataSimulator.h"
#include "OrderManagementSystem.h"
#include "MarketMakingStrategy.h"
#include "OrderExecutionEngine.h"
#include "RiskManagement.h"
#include "PerformanceMetricsAnalysis.h"

class SimulationEnvironment {
private:
    MarketDataSimulator marketDataSimulator;
    OrderManagementSystem orderManagementSystem;
    MarketMakingStrategy marketMakingStrategy;
    OrderExecutionEngine orderExecutionEngine;
    RiskManagement riskManagement;
    PerformanceMetricsAnalysis performanceMetricsAnalysis;

public:
    SimulationEnvironment();
    void runSimulation();
    // Add more functions or members as needed
};

#endif /* SIMULATIONENVIRONMENT_H */

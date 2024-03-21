#ifndef PERFORMANCEMETRICSANALYSIS_H
#define PERFORMANCEMETRICSANALYSIS_H

#include <vector>

struct Trade {
    double price;
    int quantity;
};

class PerformanceMetricsAnalysis {
public:
    double calculateAveragePrice(const std::vector<Trade>& trades);
    // Add more functions or members as needed
};

#endif /* PERFORMANCEMETRICSANALYSIS_H */

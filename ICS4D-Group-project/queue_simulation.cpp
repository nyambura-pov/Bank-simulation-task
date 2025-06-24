#include <iostream>
#include <iomanip>
#include <vector>
#include <random>
#include <algorithm>

struct Customer {
    int id;
    double arrivalTime;
    double serviceTime;
    double serviceStart;
    double serviceEnd;
    double waitingTime;
    double timeInSystem;
};

int main() {
    const int NUM_CUSTOMERS = 100;
    std::vector<Customer> customers;
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<> arrivalDist(1.0, 8.0);  // Uniform(1, 8)
    std::uniform_real_distribution<> serviceDist(1.0, 6.0);  // Uniform(1, 6)

    double lastServiceEnd = 0.0;

    std::cout << std::fixed << std::setprecision(2);
    std::cout << std::setw(10) << "Customer"
        << std::setw(15) << "Arrival Time"
        << std::setw(15) << "Service Time"
        << std::setw(15) << "Service Start"
        << std::setw(15) << "Waiting Time"
        << std::setw(15) << "Service End"
        << std::setw(18) << "Time in System" << "\n";

    for (int i = 1; i <= NUM_CUSTOMERS; ++i) {
        Customer c;
        c.id = i;
        c.arrivalTime = arrivalDist(gen);
        c.serviceTime = serviceDist(gen);
        c.serviceStart = std::max(c.arrivalTime, lastServiceEnd);
        c.waitingTime = c.serviceStart - c.arrivalTime;
        c.serviceEnd = c.serviceStart + c.serviceTime;
        c.timeInSystem = c.serviceEnd - c.arrivalTime;

        customers.push_back(c);
        lastServiceEnd = c.serviceEnd;

        std::cout << std::setw(10) << c.id
            << std::setw(15) << c.arrivalTime
            << std::setw(15) << c.serviceTime
            << std::setw(15) << c.serviceStart
            << std::setw(15) << c.waitingTime
            << std::setw(15) << c.serviceEnd
            << std::setw(18) << c.timeInSystem << "\n";
    }

    return 0;
}
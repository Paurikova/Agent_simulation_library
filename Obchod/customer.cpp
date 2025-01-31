#include "customer.h"

//functions
void customer::checkNewCustomer(int pSender, SimTime_t pExecTime) {
    int number = rand() % 2;
    std::cout << "Customer: " << number << std::endl;
    // Should be new customer generated?
    if (number == 1) {
        // new customer is created
        //send him to shop
        sendMessage(2, pExecTime, pSender, 3);
    }
}

void customer::registerFunctions() {
    registerFunction(1, [this](int pSender, SimTime_t pExecTime) {
        checkNewCustomer(pSender, pExecTime);
    });
}
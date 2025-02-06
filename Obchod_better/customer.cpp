#include "customer.h"

//functions
void Customer::createCustomer(int pSender, int pReceiver, SimTime_t pExecTime, std::unordered_map<std::string, variant_t> args) {
    logger->log(fmt::format("{}: createCustomer", pReceiver));
    int isCreated = rand() % 2;
    // Should be new customer created?
    if (isCreated == 1) {
        nCustomers += 1;
        logger->log(fmt::format("  [{}]\n", nCustomers));
        // new customer is created
        //send him to shop
        sendMessage(2, pExecTime, pReceiver, pSender);
    } else {
        std::cout << std::endl;
    }
}

void Customer::registerFunctions() {
    registerFunction(1, [this](int pSender, int pReceiver, SimTime_t pExecTime, std::unordered_map<std::string, variant_t> args) {
        createCustomer(pSender, pReceiver, pExecTime, args);
    });
}
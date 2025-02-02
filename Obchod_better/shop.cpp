#include "shop.h"
#include <cstdlib>  // For rand() and srand()
#include <ctime>    // For time()
#include <iostream>  // For std::cout

//functions
void Shop::open(int pSender, int pReceiver, SimTime_t pExecTime) {
    std::cout << pReceiver << ": open" << std::endl;
    std::cout << "Shopping is open" << std::endl;
}

void Shop::close(int pSender, int pReceiver, SimTime_t pExecTime) {
    std::cout << pReceiver << ": close" << std::endl;
    std::cout << "Shop is close" << std::endl;
}

void Shop::newCustomer(int pSender, int pReceiver, SimTime_t pExecTime) {
    std::cout << pReceiver << ": newCustomer";
    nCustomers += 1;
    int shoppingTime = rand() % shopping + shopping;
    std::cout <<"    [" << nCustomers << "]" << " Shopping time [" << shoppingTime << "]" << std::endl;
    //chose cash random
    int line = rand() % 2;
    if (line == 0) {
        sendMessage(1,pExecTime + shoppingTime, pReceiver,4);
    } else {
        sendMessage(1,pExecTime + shoppingTime, pReceiver,5);
    }
}

void Shop::removeCustomer(int pSender, int pReceiver, SimTime_t pExecTime) {
    std::cout << pReceiver << ": removeCustomer";
    nCustomers -= 1;
    std::cout << "  [" << nCustomers << "]" << std::endl;
    if (nCustomers > 0) {
        sendMessage(4, pExecTime + 1, pReceiver, pSender);
    }
}

void Shop::registerFunctions() {
    // Register a lambda function to handle function
    registerFunction(1, [this](int pSender, int pReceiver, SimTime_t pExecTime) {
        open(pSender, pReceiver, pExecTime);
    });
    registerFunction(2, [this](int pSender, int pReceiver, SimTime_t pExecTime) {
        close(pSender, pReceiver, pExecTime);
    });
    registerFunction(3, [this](int pSender, int pReceiver, SimTime_t pExecTime) {
        newCustomer(pSender, pReceiver, pExecTime);
    });
    registerFunction(4, [this](int pSender, int pReceiver, SimTime_t pExecTime) {
        removeCustomer(pSender, pReceiver, pExecTime);
    });
}
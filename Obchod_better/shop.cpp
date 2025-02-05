#include "shop.h"
#include <cstdlib>  // For rand() and srand()
#include <ctime>    // For time()
#include <iostream>  // For std::cout

//functions
void Shop::open(int pSender, int pReceiver, SimTime_t pExecTime, std::unordered_map<std::string, variant_t> args) {
    std::cout << pReceiver << ": open" << std::endl;
    std::cout << "Shopping is open" << std::endl;
}

void Shop::close(int pSender, int pReceiver, SimTime_t pExecTime, std::unordered_map<std::string, variant_t> args) {
    std::cout << pReceiver << ": close" << std::endl;
    std::cout << "Shop is close" << std::endl;
}

void Shop::newCustomer(int pSender, int pReceiver, SimTime_t pExecTime, std::unordered_map<std::string, variant_t> args) {
    std::cout << pReceiver << ": newCustomer";
    nCustomers += 1;
    int shoppingTime = rand() % shopping + shopping;
    std::cout <<" [" << nCustomers << "]" << " Shopping time [" << shoppingTime << "]" << std::endl;
    sendMessage(5,pExecTime + shoppingTime, pReceiver, pReceiver);
}

void Shop::removeCustomer(int pSender, int pReceiver, SimTime_t pExecTime, std::unordered_map<std::string, variant_t> args) {
    std::cout << pReceiver << ": removeCustomer";
    nCustomers -= 1;
    std::cout << "  [" << nCustomers << "]" << std::endl;
    if (nCustomers > 0) {
        sendMessage(4, pExecTime + 1, pReceiver, pSender);
    }
}

void Shop::endShoppingTime(int pSender, int pReceiver, SimTime_t pExecTime, std::unordered_map<std::string, variant_t> args) {
    std::cout << pReceiver << ": endShoppingTime" << std::endl;
    sendMessage(5, pExecTime, pReceiver, 4);
    sendMessage(5, pExecTime, pReceiver, 5);
}

void Shop::custInLinesCheck(int pSender, int pReceiver, SimTime_t pExecTime, std::unordered_map<std::string, variant_t> args) {
    std::cout << pReceiver << ": custInLineCheck";
    auto it = args.find("custInLine");
    int custInLine = std::get<int>(it->second);
    if (pSender == 4) {
        custInLines[0] = custInLine;
    } else {
        custInLines[1] = custInLine;
    }
    if (custInLines[0] != -1 && custInLines[1] != -1) {
        std::cout <<"   Line1[" << custInLines[0] << "]" << "     Line2 [" << custInLines[1] << "]";
        if (custInLines[0] >= custInLines[1]) {
            sendMessage(1,pExecTime, pReceiver,5);
        } else {
            sendMessage(1,pExecTime, pReceiver,4);
        }
        custInLines[0] = -1;
        custInLines[1] = -1;
    }
    std::cout << std::endl;
}

void Shop::registerFunctions() {
    // Register a lambda function to handle function
    registerFunction(1, [this](int pSender, int pReceiver, SimTime_t pExecTime, std::unordered_map<std::string, variant_t> args) {
        open(pSender, pReceiver, pExecTime, args);
    });
    registerFunction(2, [this](int pSender, int pReceiver, SimTime_t pExecTime, std::unordered_map<std::string, variant_t> args) {
        close(pSender, pReceiver, pExecTime, args);
    });
    registerFunction(3, [this](int pSender, int pReceiver, SimTime_t pExecTime, std::unordered_map<std::string, variant_t> args) {
        newCustomer(pSender, pReceiver, pExecTime, args);
    });
    registerFunction(4, [this](int pSender, int pReceiver, SimTime_t pExecTime, std::unordered_map<std::string, variant_t> args) {
        removeCustomer(pSender, pReceiver, pExecTime, args);
    });
    registerFunction(5, [this](int pSender, int pReceiver, SimTime_t pExecTime, std::unordered_map<std::string, variant_t> args) {
        endShoppingTime(pSender, pReceiver, pExecTime, args);
    });
    registerFunction(6, [this](int pSender, int pReceiver, SimTime_t pExecTime, std::unordered_map<std::string, variant_t> args) {
        custInLinesCheck(pSender, pReceiver, pExecTime, args);
    });
}
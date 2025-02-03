#include "line.h"

void Line::addToLine(int pSender, int pReceiver, SimTime_t pExecTime, std::unordered_map<std::string, std::variant<int, double, std::string>> args) {
    std::cout << pReceiver << ": addToLine";
    custInLine += 1;
    std::cout << "  [" << custInLine << "]" << std::endl;
    if (custInLine == 1) {
        sendMessage(1, pExecTime, pReceiver, pReceiver + 2);
    }
}

void Line::removeFromLine(int pSender, int pReceiver, SimTime_t pExecTime, std::unordered_map<std::string, std::variant<int, double, std::string>> args) {
    std::cout << pReceiver << ": removeFromLine";
    custInLine -= 1;
    std::cout << "  [" << custInLine << "]" << std::endl;
    //process customer by cash
    sendMessage(2, pExecTime, pReceiver, pSender);
}

void Line::removeFromShop(int pSender, int pReceiver, SimTime_t pExecTime, std::unordered_map<std::string, std::variant<int, double, std::string>> args) {
    std::cout << pReceiver << ": removeFromShop" << std::endl;
    sendMessage(4, pExecTime, pReceiver, 3);
}

void Line::hasCustomer(int pSender, int pReceiver, SimTime_t pExecTime, std::unordered_map<std::string, std::variant<int, double, std::string>> args) {
    std::cout << pReceiver << ": hasCustomer" << std::endl;
    if (custInLine > 0) {
        sendMessage(1, pExecTime, pReceiver, pReceiver + 2);
    }
}

void Line::getCountOfCustInLine(int pSender, int pReceiver, SimTime_t pExecTime, std::unordered_map<std::string, std::variant<int, double, std::string>> args) {
    std::cout << pReceiver << ": getCountOfCustInLine" << std::endl;
    sendMessage(6, pExecTime, pReceiver, pSender, -1, std::unordered_map<std::string, std::variant<int, double, std::string>>{{"custInLine", custInLine}});
}

void Line::registerFunctions() {
    // Register a lambda function to handle function
    registerFunction(1, [this](int pSender, int pReceiver, SimTime_t pExecTime, std::unordered_map<std::string, std::variant<int, double, std::string>> args) {
        addToLine(pSender, pReceiver, pExecTime, args);
    });
    registerFunction(2, [this](int pSender, int pReceiver, SimTime_t pExecTime, std::unordered_map<std::string, std::variant<int, double, std::string>> args) {
        removeFromLine(pSender, pReceiver, pExecTime, args);
    });
    registerFunction(3, [this](int pSender, int pReceiver, SimTime_t pExecTime, std::unordered_map<std::string, std::variant<int, double, std::string>> args) {
        removeFromShop(pSender, pReceiver, pExecTime, args);
    });
    registerFunction(4, [this](int pSender, int pReceiver, SimTime_t pExecTime, std::unordered_map<std::string, std::variant<int, double, std::string>> args) {
        hasCustomer(pSender, pReceiver, pExecTime, args);
    });
    registerFunction(5, [this](int pSender, int pReceiver, SimTime_t pExecTime, std::unordered_map<std::string, std::variant<int, double, std::string>> args) {
        getCountOfCustInLine(pSender, pReceiver, pExecTime, args);
    });
}

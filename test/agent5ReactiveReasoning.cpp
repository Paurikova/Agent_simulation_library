//TODO incluce
#include "agent5ReactiveReasoning.h"
void Agent5ReactiveReasoning::processCustomer(int pSender, int pReceiver, SimTime_t pExecTime, std::unordered_map<std::string, std::variant<int, double, std::string>> args) {
    //add your code
}
void Agent5ReactiveReasoning::acceptCustomer(int pSender, int pReceiver, SimTime_t pExecTime, std::unordered_map<std::string, std::variant<int, double, std::string>> args) {
    //add your code
}

void Agent5ReactiveReasoning::registerFunctions() {
    //registration
    registerFunction(2, [this](int pSender, int pReceiver, SimTime_t pExecTime, std::unordered_map<std::string, std::variant<int, double, std::string>> args) {
        processCustomer(pSender, pReceiver, pExecTime, args);
    });
    registerFunction(1, [this](int pSender, int pReceiver, SimTime_t pExecTime, std::unordered_map<std::string, std::variant<int, double, std::string>> args) {
        acceptCustomer(pSender, pReceiver, pExecTime, args);
    });
}
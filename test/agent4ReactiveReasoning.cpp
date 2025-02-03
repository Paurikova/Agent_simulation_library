//TODO incluce
#include "agent4ReactiveReasoning.h"
void Agent4ReactiveReasoning::hasCustomer(int pSender, int pReceiver, SimTime_t pExecTime, std::unordered_map<std::string, std::variant<int, float, std::string, std::vector<float>>> args) {
    //add your code
}
void Agent4ReactiveReasoning::removeFromShop(int pSender, int pReceiver, SimTime_t pExecTime, std::unordered_map<std::string, std::variant<int, float, std::string, std::vector<float>>> args) {
    //add your code
}
void Agent4ReactiveReasoning::NremoveFromLine(int pSender, int pReceiver, SimTime_t pExecTime, std::unordered_map<std::string, std::variant<int, float, std::string, std::vector<float>>> args) {
    //add your code
}
void Agent4ReactiveReasoning::addToLine(int pSender, int pReceiver, SimTime_t pExecTime, std::unordered_map<std::string, std::variant<int, float, std::string, std::vector<float>>> args) {
    //add your code
}

void Agent4ReactiveReasoning::registerFunctions() {
    //registration
    registerFunction(4, [this](int pSender, int pReceiver, SimTime_t pExecTime, std::unordered_map<std::string, std::variant<int, float, std::string, std::vector<float>>> args) {
        hasCustomer(pSender, pReceiver, pExecTime, args);
    });
    registerFunction(3, [this](int pSender, int pReceiver, SimTime_t pExecTime, std::unordered_map<std::string, std::variant<int, float, std::string, std::vector<float>>> args) {
        removeFromShop(pSender, pReceiver, pExecTime, args);
    });
    registerFunction(2, [this](int pSender, int pReceiver, SimTime_t pExecTime, std::unordered_map<std::string, std::variant<int, float, std::string, std::vector<float>>> args) {
        NremoveFromLine(pSender, pReceiver, pExecTime, args);
    });
    registerFunction(1, [this](int pSender, int pReceiver, SimTime_t pExecTime, std::unordered_map<std::string, std::variant<int, float, std::string, std::vector<float>>> args) {
        addToLine(pSender, pReceiver, pExecTime, args);
    });
}
//TODO incluce
#include "agent2ReactiveReasoning.h"
void Agent2ReactiveReasoning::createCustomer(int pSender, int pReceiver, SimTime_t pExecTime, std::unordered_map<std::string, std::variant<int, float, std::string, std::vector<float>>> args) {
    //add your code
}

void Agent2ReactiveReasoning::registerFunctions() {
    //registration
    registerFunction(1, [this](int pSender, int pReceiver, SimTime_t pExecTime, std::unordered_map<std::string, std::variant<int, float, std::string, std::vector<float>>> args) {
        createCustomer(pSender, pReceiver, pExecTime, args);
    });
}
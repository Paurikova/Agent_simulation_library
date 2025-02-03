//TODO incluce
#include "agent5ReactiveReasoning.h"
void Agent5ReactiveReasoning::processCustomer(int pSender, int pReceiver, SimTime_t pExecTime, std::unordered_map<std::string, std::variant<int, float, std::string, std::vector<float>>> args) {
    //add your code
}
void Agent5ReactiveReasoning::acceptCustomer(int pSender, int pReceiver, SimTime_t pExecTime, std::unordered_map<std::string, std::variant<int, float, std::string, std::vector<float>>> args) {
    //add your code
}

void Agent5ReactiveReasoning::registerFunctions() {
    //registration
    registerFunction(2, [this](int pSender, int pReceiver, SimTime_t pExecTime, std::unordered_map<std::string, std::variant<int, float, std::string, std::vector<float>>> args) {
        processCustomer(pSender, pReceiver, pExecTime, args);
    });
    registerFunction(1, [this](int pSender, int pReceiver, SimTime_t pExecTime, std::unordered_map<std::string, std::variant<int, float, std::string, std::vector<float>>> args) {
        acceptCustomer(pSender, pReceiver, pExecTime, args);
    });
}
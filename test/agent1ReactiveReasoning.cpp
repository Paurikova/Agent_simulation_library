//TODO incluce
#include "agent1ReactiveReasoning.h"
void Agent1ReactiveReasoning::initMessage() {
    // Add implementation of initial message
    // Replace:
    //      pServiceId by required service ID
    //      pExecTime by execution time of event
    //      pReceiver by the ID of the receiving agent
    sendMessage(pServiceId, pExecTime, 1, pReceiver, 1);
}
void Agent1ReactiveReasoning::acceptCustomer(int pSender, int pReceiver, SimTime_t pExecTime, std::unordered_map<std::string, std::variant<int, double, std::string>> args) {
    //add your code
}
void Agent1ReactiveReasoning::generateCustomer(int pSender, int pReceiver, SimTime_t pExecTime, std::unordered_map<std::string, std::variant<int, double, std::string>> args) {
    //add your code
}

void Agent1ReactiveReasoning::registerFunctions() {
    //registration
    registerFunction(2, [this](int pSender, int pReceiver, SimTime_t pExecTime, std::unordered_map<std::string, std::variant<int, double, std::string>> args) {
        acceptCustomer(pSender, pReceiver, pExecTime, args);
    });
    registerFunction(1, [this](int pSender, int pReceiver, SimTime_t pExecTime, std::unordered_map<std::string, std::variant<int, double, std::string>> args) {
        generateCustomer(pSender, pReceiver, pExecTime, args);
    });
}
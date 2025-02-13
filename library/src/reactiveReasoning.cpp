#include "../include/reactiveReasoning.h"


void ReactiveReasoning::process(ServiceId_t pServiceId, AgentId_t pSender, AgentId_t  pReceiver, SimTime_t pExecTime, State* state) {
    // Find function connected with the entered service ID
    auto it = functionMap.find(pServiceId);
    if (it != functionMap.end()) {
        it->second(pSender, pReceiver, pExecTime, state);
        return;
    }
    throw std::runtime_error(
            "Function with service ID " + std::to_string(pServiceId) + " does not exist in the map.");
}

bool ReactiveReasoning::providedService(ServiceId_t pServiceId) {
    return functionMap.find(pServiceId) != functionMap.end();
}

void ReactiveReasoning::unregisterFunction(ServiceId_t pServiceId) {
    auto it = functionMap.find(pServiceId);
    if (it != functionMap.end()) {
        functionMap.erase(it);
    } else {
        throw std::runtime_error("Function with service ID " + std::to_string(pServiceId) + " does not exist in the map");
    }
}

void ReactiveReasoning::registerFunction(ServiceId_t pServiceId, ExecFunct_t pFunc) {
    functionMap[pServiceId] = std::move(pFunc);
}

void ReactiveReasoning::initialization() {
    registerFunctions();
}
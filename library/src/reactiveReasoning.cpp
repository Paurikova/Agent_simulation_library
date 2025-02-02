#include "../include/reactiveReasoning.h"


void ReactiveReasoning::process(ServiceId_t pServiceId, AgentId_t pSender, AgentId_t  pReceiver, SimTime_t pExecTime) {
    // Find function connected with the entered service ID
    auto it = functionMap.find(pServiceId);
    if (it != functionMap.end()) {
        it->second(pSender, pReceiver, pExecTime);
        return;
    }
    // Throw an exception if the function does not exist
    throw std::runtime_error(
            "Function with service ID " + std::to_string(pServiceId) + " does not exist in the map.");
}

bool ReactiveReasoning::providedService(ServiceId_t pServiceId) {
    return functionMap.find(pServiceId) != functionMap.end();
}

void ReactiveReasoning::unregisterFunction(ServiceId_t pServiceId) {
    // Find the function pointer associated with the event ID
    auto it = functionMap.find(pServiceId);
    if (it != functionMap.end()) {
        // If the function pointer is found, remove it from the map
        functionMap.erase(it);
    } else {
        // If the function with the specified event ID does not exist, throw an exception
        throw std::runtime_error("Function with service ID " + std::to_string(pServiceId) + " does not exist in the map");
    }
}

void ReactiveReasoning::registerFunction(ServiceId_t pServiceId, ExecFunct_t pFunc) {
    // Add the function pointer to the function map
    functionMap[pServiceId] = std::move(pFunc);
}

void ReactiveReasoning::initialization() {
    registerFunctions();
}
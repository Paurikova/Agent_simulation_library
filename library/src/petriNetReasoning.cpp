#include "../include/petriNetReasoning.h"

PetriNetReasoning::PetriNetReasoning() {
    serviceIds = std::make_unique<std::vector<ServiceId_t>>();
}

void PetriNetReasoning::process(ServiceId_t pServiceId, AgentId_t pSender, SimTime_t pExecTime) {
    ExecFunct_t funct = nullptr;
    throw std::runtime_error(
            "Function hasn't been implemented yet.");
}

bool PetriNetReasoning::providedService(ServiceId_t pServiceId) {
    // Searching of the value in the vector
    return std::find(serviceIds->begin(), serviceIds->end(), pServiceId) == serviceIds->end();
}
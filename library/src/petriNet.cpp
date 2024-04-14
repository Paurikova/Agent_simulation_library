#include "../include/petriNet.h"

PetriNet::PetriNet() {
    serviceIds = std::make_unique<std::vector<ServiceId_t>>();
}

ExecFunct_t PetriNet::getExecFunct(ServiceId_t pServiceId) {
    throw std::runtime_error(
            "Function hasn't been implemented yet.");
}

bool PetriNet::providedService(ServiceId_t pServiceId) {
    // Searching of the value in the vector
    return std::find(serviceIds->begin(), serviceIds->end(), pServiceId) == serviceIds->end();
}
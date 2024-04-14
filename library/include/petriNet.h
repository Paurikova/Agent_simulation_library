#pragma once

#include <iostream>
#include <memory>
#include <vector>
#include <algorithm>

#include "types.h"

/**
 * @brief The PetriNet class represents a Petri net.
 */
class PetriNet {
private:
    std::unique_ptr<std::vector<ServiceId_t>> serviceIds; /**< Unique pointer to a vector of service IDs. */
public:
    /**
     * @brief Constructs a PetriNet object.
     */
    PetriNet();

    /**
    * @brief Retrieves the execution function associated with a service ID.
    *
    * @param pServiceId The service ID.
    * @return The execution function associated with the service ID.
    */
    ExecFunct_t getExecFunct(ServiceId_t pServiceId);

    /**
    * @brief Checks if a service is provided.
    *
    * @param pServiceId The service ID to check.
    * @return True if the service is provided, false otherwise.
    */
    bool providedService(ServiceId_t pServiceId);
};
#pragma once

#include <iostream>
#include <memory>
#include <vector>
#include <algorithm>

#include "types.h"
#include "agentReasoning.h"

/**
 * @brief The PetriNet class represents a Petri net.
 */
class IntelligentReasoning : public AgentReasoning {
private:
    std::unique_ptr<std::vector<ServiceId_t>> serviceIds; /**< Unique pointer to a vector of service IDs. */
public:
    /**
     * @brief Constructs a PetriNet object.
     */
    IntelligentReasoning();

    /**
    * @brief Retrieves the execution function associated with a service ID.
    *
    * @param pServiceId The service ID.
    * @return The execution function associated with the service ID.
    */
    void process(ServiceId_t pServiceId, AgentId_t pSender) override;

    /**
    * @brief Checks if a service is provided.
    *
    * @param pServiceId The service ID to check.
    * @return True if the service is provided, false otherwise.
    */
    bool providedService(ServiceId_t pServiceId) override;

    void initialization() override;
};
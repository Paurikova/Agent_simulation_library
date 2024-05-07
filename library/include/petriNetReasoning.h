#pragma once

#include <iostream>
#include <memory>
#include <vector>
#include <algorithm>

#include "types.h"
#include "agentReasoning.h"

/**
 * @brief Class representing Petri net reasoning functionality, derived from AgentReasoning.
 */
class PetriNetReasoning : public AgentReasoning {
private:
    std::unique_ptr<std::vector<ServiceId_t>> serviceIds; /**< Unique pointer to a vector of service IDs. */
public:
    /**
     * @brief Default constructor for PetriNetReasoning class.
     */
    PetriNetReasoning();

    /**
     * @brief Retrieves the execution function associated with a service ID.
     *
     * @param pServiceId The service ID.
     * @param pSender The ID of the sender agent.
     * @param execTime The execution time.
     */
    void process(ServiceId_t pServiceId, AgentId_t pSender, SimTime_t pExecTime) override;

    /**
     * @brief Checks if a service is provided.
     *
     * @param pServiceId The service ID to check.
     * @return True if the service is provided, false otherwise.
     */
    bool providedService(ServiceId_t pServiceId) override;

    /**
    * @brief Initialization method.
    */
    void initialization() override;
};
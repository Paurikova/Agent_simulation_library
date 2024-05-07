#pragma once
#include "types.h"

class AgentReasoning {
public:
    /**
     * @brief Retrieves the execution function associated with a service ID.
     *
     * @param pServiceId The service ID.
     * @return The execution function associated with the service ID.
     */
    virtual void process(ServiceId_t pServiceId, AgentId_t pSender) = 0;

    /**
    * @brief Checks if a service is provided.
    *
    * @param pServiceId The service ID to check.
    * @return True if the service is provided, false otherwise.
    */
    virtual bool providedService(ServiceId_t pServiceId) = 0;

    virtual void initialization() = 0;
};

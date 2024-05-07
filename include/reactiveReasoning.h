#pragma once
#include <iostream>
#include "types.h"
#include "agentReasoning.h"

class ReactiveReasoning : public AgentReasoning {
private:
    std::unordered_map<ServiceId_t, ExecFunct_t> functionMap; /**< Maps functions to service IDs. */
public:
    ReactiveReasoning(){};
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

    void registerFunction(ServiceId_t pServiceId, ExecFunct_t pFunc);
    void unregisterFunction(ServiceId_t pServiceId);
    /**
    * @brief Registers functions for handling events.
    *
    * This method must be implemented by derived classes.
    */
    virtual void registerFunctions() = 0;
    void initialization() override;
};

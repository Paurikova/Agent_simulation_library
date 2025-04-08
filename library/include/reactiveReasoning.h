#pragma once
#include <iostream>
#include "types_library.h"
#include "agentReasoning.h"

/**
 * @brief Class for reactive reasoning functionality, derived from AgentReasoning.
 */
class ReactiveReasoning : public AgentReasoning {
private:
    std::map<ServiceId_t, ExecFunct_t> functionMap; /**< Maps functions to service IDs. */

protected:
    /**
     * @brief Registers a function for handling events.
     *
     * @param pServiceId The ID of the service.
     * @param pFunc The execution function associated with the service ID.
     */
    void registerFunction(ServiceId_t pServiceId, ExecFunct_t pFunc);

    /**
     * @brief Unregisters a function associated with a service ID.
     *
     * @param pServiceId The ID of the service.
     */
    void unregisterFunction(ServiceId_t pServiceId);

    /**
    * @brief Registers functions for handling events.
    *
    * This method must be implemented by derived classes.
    */
    virtual void registerFunctions() = 0;

public:
    /**
     * @brief Default constructor for ReactiveReasoning class.
     *
     * @param pLogger Inherited
     */
    ReactiveReasoning(Logger* pLogger) : AgentReasoning(pLogger) {};

    /**
    * @brief Retrieves the execution function associated with a service ID.
    *
    * @param pServiceId The service ID.
    * @param pSender The ID of the sender agent.
     * * @param pSender The ID of the receiver agent.
    * @param execTime The execution time.
    */
    void process(ServiceId_t pServiceId, AgentId_t pSender, AgentId_t  pReceiver, SimTime_t pExecTime, State* state) override;

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

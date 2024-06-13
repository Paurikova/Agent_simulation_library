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
    std::unordered_map<ServiceId_t, NodeId_t> serviceToNode;
    std::unordered_map<NodeId_t, ExecNode_t> nodeFunct; /**< Maps functions to service IDs. */
protected:
    AgentId_t sender = -1;
    SimTime_t execTime = -1;
public:
    /**
     * @brief Default constructor for PetriNetReasoning class.
     */
    PetriNetReasoning(){};

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

    void registerNode(NodeId_t pId, ExecNode_t node);
    virtual void registerNodes() = 0;

    /**
    * @brief Initialization method.
    */
    void initialization() override;
};
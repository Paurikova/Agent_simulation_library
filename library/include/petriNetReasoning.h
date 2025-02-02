#pragma once

#include <iostream>
#include <memory>
#include <vector>
#include <algorithm>
#include <deque>
#include <unordered_set>

#include "types.h"
#include "agentReasoning.h"
#include "uniqueDeque.h"

/**
 * @brief Class representing Petri net reasoning functionality, derived from AgentReasoning.
 */
class PetriNetReasoning : public AgentReasoning {
private:
    std::unordered_map<ServiceId_t, NodeId_t> serviceToNode; /**< Maps service IDs to node IDs. */
    std::unordered_map<NodeId_t, ExecNode_t> nodeToFunct; /**< Maps node IDs to execution functions. */

protected:
    AgentId_t sender; /**< ID of the sender agent on the message. */
    SimTime_t execTime; /**< Execution time of the message. */

protected:
    /**
    * @brief Registers a service to corresponding node ID.
    * Node is a follower of the service.
    *
    * @param pServiceId The service ID.
    * @param pId The node ID.
    */
    void registerService(ServiceId_t pServiceId, NodeId_t pId);

    /**
    * @brief Unregisters a service.
    *
    * @param pServiceId The service ID.
    */
    void unregisterService(ServiceId_t pServiceId);

    /**
     * @brief Registers a node with an execution function.
     *
     * @param pId The node ID.
     * @param pNode The function to execute for the node.
     */
    void registerNode(NodeId_t pId, ExecNode_t node);

    /**
     * @brief Unregisters a node.
     *
     * @param pId The node ID.
     */
    void unregisterNode(NodeId_t pId);
    /**
    * @brief Register services to their corresponding node IDs.
    */
    virtual void registerServices() = 0;

    /**
    * @brief Register node IDs to their corresponding nodes.
    */
    virtual void registerNodes() = 0;

public:
    /**
     * @brief Default constructor for PetriNetReasoning class.
     */
    PetriNetReasoning() {};

    /**
     * @brief Retrieves the execution nodes associated with a service ID.
     *
     * @param pServiceId The service ID.
     * @param pSender The ID of the sender agent.
     * @param execTime The execution time.
     */
    void process(ServiceId_t pServiceId, AgentId_t pSender, AgentId_t  pReceiver, SimTime_t pExecTime) override;

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
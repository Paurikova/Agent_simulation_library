#include "../include/petriNetReasoning.h"

void PetriNetReasoning::registerService(ServiceId_t pServiceId, NodeId_t pId) {
    // Map the service ID to the node ID
    serviceToNode[pServiceId] = pId;
}

void PetriNetReasoning::unregisterService(ServiceId_t pServiceId) {
    // remove service ID from the map
    auto it = serviceToNode.find(pServiceId);
    if(it != serviceToNode.end()) {
        serviceToNode.erase(pServiceId);
    }
}

void PetriNetReasoning::registerNode(NodeId_t pId, ExecNode_t pNode) {
    // Add the function pointer to the function map
    nodeToFunct[pId] = std::move(pNode);
}

void PetriNetReasoning::unregisterNode(NodeId_t pId) {
    // remove node ID from the map
    auto it = nodeToFunct.find(pId);
    if(it != nodeToFunct.end()) {
        nodeToFunct.erase(pId);
    }
}

void PetriNetReasoning::process(ServiceId_t pServiceId, AgentId_t pSender, AgentId_t  pReceiver, SimTime_t pExecTime, State* state) {
    // Find the node id associated with the service
    auto it = serviceToNode.find(pServiceId);
    if (it == serviceToNode.end()) {
        // Throw an error if the service is not found
        throw std::runtime_error("Required service does not exist!");
    }

    // Set sender and execution time of the message
    sender = pSender;
    execTime = pExecTime;

    // Get the initial node ID associated with the service
    NodeId_t nodeId = serviceToNode.at(pServiceId);

    // Create a deque to store result from processed node
    NodeId_t result;
    // Process nodes in a loop until activeNodes is not -1
    while (nodeId != -1) {
        // Find the function associated with the current node ID
        auto it = nodeToFunct.find(nodeId);

        // Find the function associated with the current node ID
        if (it != nodeToFunct.end()) {
            // Execute the function and update the result
            nodeId = it->second(pSender, pReceiver, pExecTime, state);
        } else {
            // Throw an error if the node ID is not found
            throw std::runtime_error("Required node id does not exist!");
        }
    }
}

bool PetriNetReasoning::providedService(ServiceId_t pServiceId) {
    // Check if the service ID exists in the map
    auto it = serviceToNode.find(pServiceId);
    return it != serviceToNode.end();
}

void PetriNetReasoning::initialization() {
    // Register services and nodes
    registerServices();
    registerNodes();
}
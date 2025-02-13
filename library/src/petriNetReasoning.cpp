#include "../include/petriNetReasoning.h"

void PetriNetReasoning::registerService(ServiceId_t pServiceId, NodeId_t pId) {
    serviceToNode[pServiceId] = pId;
}

void PetriNetReasoning::unregisterService(ServiceId_t pServiceId) {
    auto it = serviceToNode.find(pServiceId);
    if(it != serviceToNode.end()) {
        serviceToNode.erase(pServiceId);
    }
}

void PetriNetReasoning::registerNode(NodeId_t pId, ExecNode_t pNode) {
    nodeToFunct[pId] = std::move(pNode);
}

void PetriNetReasoning::unregisterNode(NodeId_t pId) {
    auto it = nodeToFunct.find(pId);
    if(it != nodeToFunct.end()) {
        nodeToFunct.erase(pId);
    }
}

void PetriNetReasoning::process(ServiceId_t pServiceId, AgentId_t pSender, AgentId_t  pReceiver, SimTime_t pExecTime, State* state) {
    // Find the node id associated with the service
    auto it = serviceToNode.find(pServiceId);
    if (it == serviceToNode.end()) {
        throw std::runtime_error("Required service does not exist!");
    }

    sender = pSender;
    execTime = pExecTime;

    NodeId_t nodeId = serviceToNode.at(pServiceId);

    NodeId_t result;
    // Process nodes in a loop until activeNodes is not -1
    while (nodeId != UNDEFINATED_NODE) {
        auto it = nodeToFunct.find(nodeId);
        if (it != nodeToFunct.end()) {
            // Execute the function and update the result
            nodeId = it->second(pSender, pReceiver, pExecTime, state);
        } else {
            throw std::runtime_error("Required node id does not exist!");
        }
    }
}

bool PetriNetReasoning::providedService(ServiceId_t pServiceId) {
    auto it = serviceToNode.find(pServiceId);
    return it != serviceToNode.end();
}

void PetriNetReasoning::initialization() {
    registerServices();
    registerNodes();
}
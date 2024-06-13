#include "../include/petriNetReasoning.h"

void PetriNetReasoning::process(ServiceId_t pServiceId, AgentId_t pSender, SimTime_t pExecTime) {
    auto it = serviceToNode.find(pServiceId);
    if (it == serviceToNode.end()) {
        throw std::runtime_error("Required service does not exist!");
    }
    sender = pSender;
    execTime = pExecTime;
    NodeId_t nodeId = serviceToNode.at(pServiceId);
    while (nodeId != -1) {
        auto it = nodeFunct.find(nodeId);
        if (it != nodeFunct.end()) {
            nodeId = it->second();
        } else {
            throw std::runtime_error("Required node id does not exist!");
        }
    }
}

bool PetriNetReasoning::providedService(ServiceId_t pServiceId) {
    // Searching of the value in the vector
    auto it = serviceToNode.find(pServiceId);
    return it != serviceToNode.end();
}

void PetriNetReasoning::initialization() {
    registerNodes();
}

void PetriNetReasoning::registerNode(NodeId_t pId, ExecNode_t node) {
    // Add the function pointer to the function map
    nodeFunct[pId] = std::move(node);
}
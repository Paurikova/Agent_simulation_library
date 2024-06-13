#include "backend/include/agent1PetriNetReasoning.h"

NodeId_t Agent1PetriNetReasoning::condition1() {
    return 1;
}

void Agent1PetriNetReasoning::registerNodes() {
    registerNode(1, [this]() {
        return condition1();
    });
}
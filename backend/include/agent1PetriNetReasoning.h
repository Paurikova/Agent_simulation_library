#pragma once
#include "../../library/include/petriNetReasoning.h"
class Agent1PetriNetReasoning : public PetriNetReasoning {
private:
    NodeId_t condition1();
    NodeId_t code2();
    NodeId_t funct3();
    NodeId_t funct4();
    void registerNodes() override;
    void registerServices() override;
};
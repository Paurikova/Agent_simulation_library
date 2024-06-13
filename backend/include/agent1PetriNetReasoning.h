#pragma once
#include "../../library/include/petriNetReasoning.h"
class Agent1PetriNetReasoning : public PetriNetReasoning {
private:
    NodeId_t condition1();
public:
    void registerNodes() override;
};
#pragma once
//TODO incluce
#include "../../library/include/petriNetReasoning.h"
#include <string>

using namespace std;

class Line5PetriNetReasoning : public PetriNetReasoning {
private:
    //attributes
    StateShop* stateShop = nullptr;
    //nodes
    NodeId_t hasCustomer_fun1_fun363();
    NodeId_t Condition_cond358();
    NodeId_t removeFromShop_fun355();
    NodeId_t removeFromLine_fun352();
    NodeId_t addToLine_fun1_fun349();
    NodeId_t Condition_cond344();
    void registerNodes() override;
    void registerServices() override;
};

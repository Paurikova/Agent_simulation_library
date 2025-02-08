#pragma once
#include <cstdlib> // For rand()

#include "../../../../library/include/petriNetReasoning.h"
#include "state_shop.h"

class Customer : public PetriNetReasoning {
private:
    StateShop* stateShop;
    //function
    NodeId_t createCustomer(int pSender, int pReceiver, SimTime_t pExecTime, State* state);
    void registerNodes() override;
    void registerServices() override;
public:
    Customer(StateShop* pStateShop, Logger* pLogger) : PetriNetReasoning(pLogger), stateShop(pStateShop) {};
};
#pragma once
//TODO incluce
#include "../../library/include/petriNetReasoning.h"
#include <string>

using namespace std;

class Shop3PetriNetReasoning : public PetriNetReasoning {
private:
    //attributes
    int shopping = 3;
    StateShop* stateShop = nullptr;
    //nodes
    NodeId_t addCustomerToLine_fun2_fun341();
    NodeId_t addCustomerToLine_fun1_fun338();
    NodeId_t Condition_cond333();
    NodeId_t removeCustomer_fun1_fun330();
    NodeId_t Condition_cond325();
    NodeId_t newCustomer_fun322();
    NodeId_t close_fun319();
    NodeId_t open_fun316();
    void registerNodes() override;
    void registerServices() override;
};

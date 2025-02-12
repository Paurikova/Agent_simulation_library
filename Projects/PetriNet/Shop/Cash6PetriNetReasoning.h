#pragma once
//TODO incluce
#include "../../library/include/petriNetReasoning.h"
#include <string>

using namespace std;

class Cash6PetriNetReasoning : public PetriNetReasoning {
private:
    //attributes
    bool hasCustom = false;
    int processLength = 60;
    int breakLength = 100;
    std::vector<int> breaks = ;
    StateShop* stateShop = nullptr;
    //nodes
    NodeId_t endCustomer_fun389();
    NodeId_t processCustomer_fun386();
    NodeId_t acceptCustomerFun2_fun383();
    NodeId_t acceptCustomer_fun1_fun380();
    NodeId_t Condition_cond375();
    NodeId_t Code_code371();
    NodeId_t Condition_cond366();
    void registerNodes() override;
    void registerServices() override;
};

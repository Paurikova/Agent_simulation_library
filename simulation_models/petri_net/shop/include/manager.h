#include "../../../../library/include/petriNetReasoning.h"
#include "state_shop.h"
class Manager : public PetriNetReasoning {
private:
    //attributes
    int run = true;
    int newCust;
    //functions
    NodeId_t generateCustomer(int pSender, int pReceiver, SimTime_t pExecTime, State* state);
    NodeId_t acceptCustomer(int pSender, int pReceiver, SimTime_t pExecTime, State* state);
    NodeId_t closeSimulation(int pSender, int pReceiver, SimTime_t pExecTime, State* state);
    void registerNodes() override;
    void registerServices() override;
public:
    Manager(int pNewCust, Logger* pLogger) : PetriNetReasoning(pLogger),
    newCust(pNewCust) {}
    void initMessage() override;
};
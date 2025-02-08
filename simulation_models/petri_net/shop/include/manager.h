#include "../../../../library/include/reactiveReasoning.h"
#include "state_shop.h"
class Manager : public ReactiveReasoning {
private:
    //attributes
    int run = true;
    int newCust;
    //functions
    void generateCustomer(int pSender, int pReceiver, SimTime_t pExecTime, State* state);
    void acceptCustomer(int pSender, int pReceiver, SimTime_t pExecTime, State* state);
    void closeSimulation(int pSender, int pReceiver, SimTime_t pExecTime, State* state);
    void registerFunctions() override;
public:
    Manager(int pNewCust, Logger* pLogger) : ReactiveReasoning(pLogger),
                                             newCust(pNewCust) {}
    void initMessage() override;
};
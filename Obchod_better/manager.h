#include "../library/include/reactiveReasoning.h"
#include "state_shop.h"
class Manager : public ReactiveReasoning {
private:
    //attributes
    int end;
    int newCust;
    StateShop* stateShop;
    //functions
    void generateCustomer(int pSender, int pReceiver, SimTime_t pExecTime, State* state);
    void acceptCustomer(int pSender, int pReceiver, SimTime_t pExecTime, State* state);
    void registerFunctions() override;
public:
    Manager(int pEnd, int pNewCust, StateShop* pStateShop, Logger* pLogger) : ReactiveReasoning(pLogger), end(pEnd),
    newCust(pNewCust), stateShop(pStateShop) {}
    void initMessage() override;
};
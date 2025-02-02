#include "../library/include/reactiveReasoning.h"

class Manager : public ReactiveReasoning {
private:
    //attributes
    int end;
    int newCust;
    //functions
    void generateCustomer(int pSender, int pReceiver, SimTime_t pExecTime);
    void acceptCustomer(int pSender, int pReceiver, SimTime_t pExecTime);
    void registerFunctions() override;
public:
    Manager(int pEnd, int pNewCust) : end(pEnd), newCust(pNewCust) {}
    void initMessage() override;
};
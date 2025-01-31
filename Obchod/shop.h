#include "../library/include/reactiveReasoning.h"
#include <iostream>

class shop : public ReactiveReasoning {
private:
    //attributes
    int nCustomers = 0;
    //functions
    void newCustomer(int pSender, SimTime_t pExecTime);
    void removedCustomer(int pSender, SimTime_t pExecTime);
    void addToLine(int pSender, SimTime_t pExecTime);
    void registerFunctions() override;
public:
    void initMessage() override;
};
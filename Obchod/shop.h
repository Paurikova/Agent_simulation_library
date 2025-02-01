#include "../library/include/reactiveReasoning.h"
#include <iostream>

class shop : public ReactiveReasoning {
private:
    //attributes
    int nCustomers = 0;
    //functions
    void newCustomer(int pSender, SimTime_t pExecTime);
    void removedCustomerLine1(int pSender, SimTime_t pExecTime);
    void removedCustomerLine2(int pSender, SimTime_t pExecTime);
    void hasCustomers1(int pSender, SimTime_t pExecTime);
    void hasCustomers2(int pSender, SimTime_t pExecTime);
    void registerFunctions() override;
public:
    void initMessage() override;
};
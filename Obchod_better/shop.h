#include "../library/include/reactiveReasoning.h"
#include <iostream>

class Shop : public ReactiveReasoning {
private:
    //attributes
    int nCustomers = 0;
    //functions
    void open(int pSender, int pReceiver, SimTime_t pExecTime);
    void close(int pSender, int pReceiver, SimTime_t pExecTime);
    void newCustomer(int pSender, int pReceiver, SimTime_t pExecTime);
    void removeCustomer(int pSender, int pReceiver, SimTime_t pExecTime);
    void hasCustomer(int pSender, int pReceiver, SimTime_t pExecTime);
    void registerFunctions() override;
};
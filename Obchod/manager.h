#include "../library/include/reactiveReasoning.h"

class Manager : public ReactiveReasoning {
private:
    //attributes
    int shopClose = 100;
    //functions
    void newCustomer(int pSender, SimTime_t pExecTime);
    void isOpen1(int pSender, SimTime_t pExecTime);
    void isOpen2(int pSender, SimTime_t pExecTime);
    void registerFunctions() override;
public:
    void initMessage() override;
};
#include "../library/include/reactiveReasoning.h"

class Manager : public ReactiveReasoning {
private:
    //attributes
    int end = 10;
    int new_c = 3;
    //functions
    void generateCustomer(int pSender, int pReceiver, SimTime_t pExecTime);
    void registerFunctions() override;
public:
    void initMessage() override;
};
#include "../library/include/reactiveReasoning.h"

class Manager : public ReactiveReasoning {
private:
    //attributes
    int end;
    int newCust;
    //functions
    void generateCustomer(int pSender, int pReceiver, SimTime_t pExecTime, std::unordered_map<std::string, variant_t> args);
    void acceptCustomer(int pSender, int pReceiver, SimTime_t pExecTime, std::unordered_map<std::string, variant_t> args);
    void registerFunctions() override;
public:
    Manager(int pEnd, int pNewCust, Logger* pLogger) : ReactiveReasoning(pLogger), end(pEnd), newCust(pNewCust) {}
    void initMessage() override;
};
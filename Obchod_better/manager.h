#include "../library/include/reactiveReasoning.h"

class Manager : public ReactiveReasoning {
private:
    //attributes
    int end;
    int newCust;
    //functions
    void generateCustomer(int pSender, int pReceiver, SimTime_t pExecTime, std::unordered_map<std::string, std::variant<int, float, std::string, std::vector<float>>> args);
    void acceptCustomer(int pSender, int pReceiver, SimTime_t pExecTime, std::unordered_map<std::string, std::variant<int, float, std::string, std::vector<float>>> args);
    void registerFunctions() override;
public:
    Manager(int pEnd, int pNewCust) : end(pEnd), newCust(pNewCust) {}
    void initMessage() override;
};
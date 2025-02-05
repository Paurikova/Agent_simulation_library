#include "../library/include/reactiveReasoning.h"
#include <iostream>

class Shop : public ReactiveReasoning {
private:
    //attributes
    int nCustomers = 0;
    int shopping;
    int custInLines[2]  = {-1, -1};
    //functions
    void open(int pSender, int pReceiver, SimTime_t pExecTime, std::unordered_map<std::string, variant_t> args);
    void close(int pSender, int pReceiver, SimTime_t pExecTime, std::unordered_map<std::string, variant_t> args);
    void newCustomer(int pSender, int pReceiver, SimTime_t pExecTime, std::unordered_map<std::string, variant_t> args);
    void removeCustomer(int pSender, int pReceiver, SimTime_t pExecTime, std::unordered_map<std::string, variant_t> args);
    void hasCustomer(int pSender, int pReceiver, SimTime_t pExecTime, std::unordered_map<std::string, variant_t> args);
    void endShoppingTime(int pSender, int pReceiver, SimTime_t pExecTime, std::unordered_map<std::string, variant_t> args);
    void custInLinesCheck(int pSender, int pReceiver, SimTime_t pExecTime, std::unordered_map<std::string, variant_t> args);
    void registerFunctions() override;
public:
    Shop(int pShopping) : shopping(pShopping) {}
};
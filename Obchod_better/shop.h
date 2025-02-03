#include "../library/include/reactiveReasoning.h"
#include <iostream>

class Shop : public ReactiveReasoning {
private:
    //attributes
    int nCustomers = 0;
    int shopping;
    int custInLines[2]  = {-1, -1};
    //functions
    void open(int pSender, int pReceiver, SimTime_t pExecTime, std::unordered_map<std::string, std::variant<int, double, std::string>> args);
    void close(int pSender, int pReceiver, SimTime_t pExecTime, std::unordered_map<std::string, std::variant<int, double, std::string>> args);
    void newCustomer(int pSender, int pReceiver, SimTime_t pExecTime, std::unordered_map<std::string, std::variant<int, double, std::string>> args);
    void removeCustomer(int pSender, int pReceiver, SimTime_t pExecTime, std::unordered_map<std::string, std::variant<int, double, std::string>> args);
    void hasCustomer(int pSender, int pReceiver, SimTime_t pExecTime, std::unordered_map<std::string, std::variant<int, double, std::string>> args);
    void endShoppingTime(int pSender, int pReceiver, SimTime_t pExecTime, std::unordered_map<std::string, std::variant<int, double, std::string>> args);
    void custInLinesCheck(int pSender, int pReceiver, SimTime_t pExecTime, std::unordered_map<std::string, std::variant<int, double, std::string>> args);
    void registerFunctions() override;
public:
    Shop(int pShopping) : shopping(pShopping) {}
};
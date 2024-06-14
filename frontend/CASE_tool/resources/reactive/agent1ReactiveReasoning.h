#pragma once
//TODO incluce
#include "../../library/include/reactiveReasoning.h"
#include <string>
using namespace std;

class Agent1ReactiveReasoning : public ReactiveReasoning {
private:
    //attributes
    //functions
    void Name(int pSender, SimTime_t pExecTime);
    //registration
    void registerFunctions() override;
public:
    void initMessage() override;
};

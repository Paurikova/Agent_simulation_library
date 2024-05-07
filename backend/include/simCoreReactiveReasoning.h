#include "../../library/include/reactiveReasoning.h"

class SimCoreReactiveReasoning : public ReactiveReasoning {
private:
    //function
    void allDone(int pSender, SimTime_t pExecTime);
public:
    void registerFunctions() override;
};
    #include "../../../petri_net/shop/include/line.h"

    //1
    NodeId_t Line::hasCustomer_cond1(int pSender, int pReceiver, SimTime_t pExecTime, State* state) {
        // add your code
        //add condition
        if () {
            return 2;
        }
        return 3;
    }

    //2
    NodeId_t Line::hasCustomer_code1(int pSender, int pReceiver, SimTime_t pExecTime, State* state) {
        // add your code
        return 3;
    }

    //3
    NodeId_t Line::hasCustomer_fun1(int pSender, int pReceiver, SimTime_t pExecTime, State* state) {
        // add your code
        return -1;
    }

    void Line::registerNodes() {
        // Register a lambda function to handle function
        registerNode(1, [this](int pSender, int pReceiver, SimTime_t pExecTime, State* state) -> NodeId_t {
            return addToLine_fun1(pSender, pReceiver, pExecTime, state);
        });
        registerNode(2, [this](int pSender, int pReceiver, SimTime_t pExecTime, State* state) -> NodeId_t {
            return hasCustomer_code1(pSender, pReceiver, pExecTime, state);
        });
        registerNode(3, [this](int pSender, int pReceiver, SimTime_t pExecTime, State* state) -> NodeId_t {
            return addToLine_fun1(pSender, pReceiver, pExecTime, state);
        });
    }

    void Line::registerServices() {
        registerService(1, 1);
    }



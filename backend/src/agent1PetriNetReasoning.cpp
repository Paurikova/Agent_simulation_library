#include "../include/agent1PetriNetReasoning.h"

NodeId_t Agent1PetriNetReasoning::condition1() {
    if (execTime > 4) {
        return 4;
    } else {
        return 2;
    }
}

NodeId_t Agent1PetriNetReasoning::code2() {
    execTime += 2;
    return 3;
}

NodeId_t Agent1PetriNetReasoning::funct3() {
    std::cout << "Funct 3" << std::endl;
    return UNDEFINATED_NODE;
}

NodeId_t Agent1PetriNetReasoning::funct4() {
    std::cout << "Funct 4" << std::endl;
    return UNDEFINATED_NODE;
}

void Agent1PetriNetReasoning::registerNodes() {
    registerNode(1, [this]()->NodeId_t {
        return condition1();
    });
    registerNode(2, [this]()->NodeId_t {
        return code2();
    });
    registerNode(3, [this]()->NodeId_t {
        return funct3();
    });
    registerNode(4, [this]()->NodeId_t {
        return funct4();
    });
}

void Agent1PetriNetReasoning::registerServices() {
    registerService(1, 1);
}
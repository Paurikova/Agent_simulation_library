//TODO include
#include/Customer2ReactiveReasoning.h
#include/Cash6PetriNetReasoning.h
#include/Line5PetriNetReasoning.h
#include/Graph4ReactiveReasoning.h
#include/Shop3PetriNetReasoning.h
#include/Manager1ReactiveReasoning.h
#include "library/include/agentManager.h"
#include "library/include/simulationCore.h"

int main(int argc, char** argv) {{
    std::unique_ptr<Logger> logger = std::make_unique<Logger>(false);
    //simulation core
    std::unique_ptr<SimulationCore> simulationCore = std::make_unique<SimulationCore>(logger.get());
    //manager
    std::unique_ptr<Manager1ReactiveReasoning> rManager1ReactiveReasoning = std::make_unique<Manager1ReactiveReasoning>(logger.get());
    std::unique_ptr<AgentManager> aManager = std::make_unique<AgentManager>(rManager1ReactiveReasoning.get(), logger.get());
    simulationCore->registerAgent(aManager.get());
    //agents
    std::unique_ptr<Customer2ReactiveReasoning> rCustomer2ReactiveReasoning = std::make_unique<Customer2ReactiveReasoning>(logger.get());
    std::unique_ptr<Agent> aCustomer2 = std::make_unique<Agent>(2, aManager.get(), rCustomer2ReactiveReasoning.get());
    simulationCore->registerAgent(aCustomer2.get());
    std::unique_ptr<Cash6PetriNetReasoning> rCash6PetriNetReasoning = std::make_unique<Cash6PetriNetReasoning>(logger.get());
    std::unique_ptr<Agent> aCash6 = std::make_unique<Agent>(6, aManager.get(), rCash6PetriNetReasoning.get());
    simulationCore->registerAgent(aCash6.get());
    std::unique_ptr<Line5PetriNetReasoning> rLine5PetriNetReasoning = std::make_unique<Line5PetriNetReasoning>(logger.get());
    std::unique_ptr<Agent> aLine5 = std::make_unique<Agent>(5, aManager.get(), rLine5PetriNetReasoning.get());
    simulationCore->registerAgent(aLine5.get());
    std::unique_ptr<Graph4ReactiveReasoning> rGraph4ReactiveReasoning = std::make_unique<Graph4ReactiveReasoning>(logger.get());
    std::unique_ptr<Agent> aGraph4 = std::make_unique<Agent>(4, aManager.get(), rGraph4ReactiveReasoning.get());
    simulationCore->registerAgent(aGraph4.get());
    std::unique_ptr<Shop3PetriNetReasoning> rShop3PetriNetReasoning = std::make_unique<Shop3PetriNetReasoning>(logger.get());
    std::unique_ptr<Agent> aShop3 = std::make_unique<Agent>(3, aManager.get(), rShop3PetriNetReasoning.get());
    simulationCore->registerAgent(aShop3.get());
    simulationCore->runSimulation(1, -1);
    logger->addToFile();
    return 0;
}}
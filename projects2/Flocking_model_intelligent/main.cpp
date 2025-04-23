//TODO include
#include/Bird2ReactiveReasoning.h
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
    simulationCore->registerAgent(aManager1.get());
    //agents
    std::unique_ptr<Bird2ReactiveReasoning> rBird2ReactiveReasoning = std::make_unique<Bird2ReactiveReasoning>(logger.get());
    std::unique_ptr<Agent> aBird2 = std::make_unique<Agent>(2, aManager.get(), rBird2ReactiveReasoning.get());
    simulationCore->registerAgent(aBird2.get());
    simulationCore->runSimulation(1, -1);
    logger->addToFile();
    return 0;
}}
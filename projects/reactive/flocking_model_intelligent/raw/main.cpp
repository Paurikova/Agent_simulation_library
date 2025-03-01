//TODO include
#include/Bird2ReactiveReasoning.h
#include/Manager1ReactiveReasoning.h
#include "library/include/agentManager.h"

int main(int argc, char** argv) {{
    std::unique_ptr<Logger> logger = std::make_unique<Logger>(false);
    //manager
    std::unique_ptr<Manager1ReactiveReasoning> rManager1ReactiveReasoning = std::make_unique<Manager1ReactiveReasoning>(logger.get());
    std::unique_ptr<AgentManager> aManager = std::make_unique<AgentManager>(rManager1ReactiveReasoning.get(), logger.get());
    //agents
    std::unique_ptr<Bird2ReactiveReasoning> rBird2ReactiveReasoning = std::make_unique<Bird2ReactiveReasoning>(logger.get());
    std::unique_ptr<Agent> aBird2 = std::make_unique<Agent>(2, aManager.get(), rBird2ReactiveReasoning.get());
    aManager->registerAgent(aBird2.get());
    aManager->runSimulation(1, -1);
    logger->addToFile();
    return 0;
}}
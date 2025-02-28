#include "../../../../../library/include/agentManager.h"

#include "../include/Bird2ReactiveReasoning.h"
#include "../include/Manager1ReactiveReasoning.h"
#include "configReader.h"

int main(int argc, char** argv) {
    srand(time(0)); // Initialize random number generator
    Logger* logger = new Logger(false);
    int n_birds = 300;
    sf::RenderWindow window(sf::VideoMode(800, 600), "Flocking Simulation");
    Manager1ReactiveReasoning* rManager = new Manager1ReactiveReasoning(n_birds, window, logger);
    AgentManager* aManager = new AgentManager(rManager, logger);
    for (int i = 0; i < n_birds; i++) {
        aManager->registerAgent(new Agent(i + 2, aManager,
                                         new Bird2ReactiveReasoning(3, 0.1, 2.0, 0.25, 0.04, 50.0, n_birds, logger)));
    }

    // Run the simulation
    aManager->runSimulation(1, -1);
    logger->addToFile();

    int size = aManager->getAgentsSize();
    for (int i = 0; i < size; i++) {
        delete aManager->getAgent(i)->getReasoning();
        delete aManager->getAgent(i);
    }
    delete rManager;
    delete aManager;
    delete logger;
    return 0;
}
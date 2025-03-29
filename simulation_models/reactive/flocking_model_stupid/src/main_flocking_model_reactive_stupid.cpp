#include "../../../../library/include/agentManager.h"
#include "../../../../library/include/agent.h"

#include "../include/bird.h"
#include "../include/manager.h"
#include "configReader.h"

int main(int argc, char** argv) {
    srand(time(0)); // Initialize random number generator
    // Create a flock of birds
    Logger* logger = new Logger(false);
    int n_birds = 500;
    sf::RenderWindow window(sf::VideoMode(800, 600), "Flocking Simulation");
    Manager* rManager = new Manager(0.5, 0.1, 2.0, 0.25, 0.04, 50.0,
                                   n_birds, window, logger);
    AgentManager* aManager = new AgentManager(rManager, logger);
    for (int i = 0; i < n_birds; i++) {
        Agent* agent = new Agent(i + 2, aManager,
                                 new Bird(logger));
        aManager->registerAgent(agent);
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
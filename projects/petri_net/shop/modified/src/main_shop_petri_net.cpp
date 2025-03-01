#include "../../../../../library/include/agentManager.h"

#include "../include/Manager1ReactiveReasoning.h"
#include "../include/Customer2ReactiveReasoning.h"
#include "../include/Shop3PetriNetReasoning.h"
#include "../include/Line5PetriNetReasoning.h"
#include "../include/Cash6PetriNetReasoning.h"
#include "../include/state_shop.h"
#include "../include/Graph4ReactiveReasoning.h"
#include "configReader.h"

int main(int argc, char** argv) {
    // Use smart pointers for automatic memory management
    std::unique_ptr<StateShop> stateShop = std::make_unique<StateShop>();
    std::unique_ptr<Logger> logger = std::make_unique<Logger>(false);

    std::unique_ptr<Manager1ReactiveReasoning> rManager = std::make_unique<Manager1ReactiveReasoning>(10, logger.get());
    std::unique_ptr<AgentManager> aManager = std::make_unique<AgentManager>(rManager.get(), logger.get());

    std::unique_ptr<Customer2ReactiveReasoning> rCustomer = std::make_unique<Customer2ReactiveReasoning>(stateShop.get(), logger.get());
    std::unique_ptr<Agent> aCustomer = std::make_unique<Agent>(2, aManager.get(), rCustomer.get());
    aManager->registerAgent(aCustomer.get());

    std::unique_ptr<Shop3PetriNetReasoning> rShop = std::make_unique<Shop3PetriNetReasoning>(15, stateShop.get(), logger.get());
    std::unique_ptr<Agent> aShop = std::make_unique<Agent>(3, aManager.get(), rShop.get());
    aManager->registerAgent(aShop.get());

    std::unique_ptr<Line5PetriNetReasoning> rLine = std::make_unique<Line5PetriNetReasoning>(stateShop.get(), logger.get());
    std::unique_ptr<Agent> aLine1 = std::make_unique<Agent>(4, aManager.get(), rLine.get());
    std::unique_ptr<Agent> aLine2 = std::make_unique<Agent>(5, aManager.get(), rLine.get());
    aManager->registerAgent(aLine1.get());
    aManager->registerAgent(aLine2.get());

    std::unique_ptr<Cash6PetriNetReasoning> rCash1 = std::make_unique<Cash6PetriNetReasoning>(std::vector<int>{100, 500, 900}, 50, 30, stateShop.get(), logger.get());
    std::unique_ptr<Cash6PetriNetReasoning> rCash2 = std::make_unique<Cash6PetriNetReasoning>(std::vector<int>{200, 600, 1000}, 50, 25, stateShop.get(), logger.get());
    std::unique_ptr<Agent> aCash1 = std::make_unique<Agent>(6, aManager.get(), rCash1.get());
    std::unique_ptr<Agent> aCash2 = std::make_unique<Agent>(7, aManager.get(), rCash2.get());
    aManager->registerAgent(aCash1.get());
    aManager->registerAgent(aCash2.get());

    sf::RenderWindow window(sf::VideoMode(800, 600), "Shop Simulation");
    std::unique_ptr<Graph4ReactiveReasoning> rGraph = std::make_unique<Graph4ReactiveReasoning>(500, window, stateShop.get(), logger.get());
    std::unique_ptr<Agent> aGraph = std::make_unique<Agent>(8, aManager.get(), rGraph.get());
    aManager->registerAgent(aGraph.get());

    aManager->runSimulation(1, -1);
    logger->addToFile();

    // No need to manually delete anything, since smart pointers take care of that.
    return 0;
}

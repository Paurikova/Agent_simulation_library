#include "../../../../../library/include/agentManager.h"

#include "../include/Manager1ReactiveReasoning.h"
#include "../include/Customer2ReactiveReasoning.h"
#include "../include/Shop3ReactiveReasoning.h"
#include "../include/Line5ReactiveReasoning.h"
#include "../include/Cash6ReactiveReasoning.h"
#include "../include/state_shop.h"
#include "../include/Graph4ReactiveReasoning.h"

int main(int argc, char** argv) {
    // Use smart pointers for automatic memory management
    std::unique_ptr<StateShop> stateShop = std::make_unique<StateShop>();
    std::unique_ptr<Logger> logger = std::make_unique<Logger>(false);

    std::unique_ptr<SimulationCore> simulationCore = std::make_unique<SimulationCore>(logger.get());

    std::unique_ptr<Manager1ReactiveReasoning> rManager = std::make_unique<Manager1ReactiveReasoning>(10, logger.get());
    std::unique_ptr<AgentManager> aManager = std::make_unique<AgentManager>(rManager.get(), logger.get());
    simulationCore->registerAgent(aManager.get());

    std::unique_ptr<Customer2ReactiveReasoning> rCustomer = std::make_unique<Customer2ReactiveReasoning>(stateShop.get(), logger.get());
    std::unique_ptr<Agent> aCustomer = std::make_unique<Agent>(2, aManager.get(), rCustomer.get());
    simulationCore->registerAgent(aCustomer.get());

    std::unique_ptr<Shop3ReactiveReasoning> rShop = std::make_unique<Shop3ReactiveReasoning>(2, stateShop.get(), logger.get());
    std::unique_ptr<Agent> aShop = std::make_unique<Agent>(3, aManager.get(), rShop.get());
    simulationCore->registerAgent(aShop.get());

    std::unique_ptr<Line5ReactiveReasoning> rLine = std::make_unique<Line5ReactiveReasoning>(stateShop.get(), logger.get());
    std::unique_ptr<Agent> aLine = std::make_unique<Agent>(4, aManager.get(), rLine.get());
    simulationCore->registerAgent(aLine.get());

    std::unique_ptr<Cash6ReactiveReasoning> rCash = std::make_unique<Cash6ReactiveReasoning>(30, 25, stateShop.get(), logger.get());
    std::unique_ptr<Agent> aCash = std::make_unique<Agent>(5, aManager.get(), rCash.get());
    simulationCore->registerAgent(aCash.get());

    sf::RenderWindow window(sf::VideoMode(800, 600), "Shop Simulation");
    std::unique_ptr<Graph4ReactiveReasoning> rGraph = std::make_unique<Graph4ReactiveReasoning>(500, window, stateShop.get(), logger.get());
    std::unique_ptr<Agent> aGraph = std::make_unique<Agent>(8, aManager.get(), rGraph.get());
    simulationCore->registerAgent(aGraph.get());

    simulationCore->runSimulation(1, -1);
    logger->addToFile();

    // No need to manually delete anything, since smart pointers take care of that.
    return 0;
}
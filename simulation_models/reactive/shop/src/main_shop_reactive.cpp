#include "../../../../library/include/simulationCore.h"

#include "../include/manager.h"
#include "../include/customer.h"
#include "../include/shop.h"
#include "../include/line.h"
#include "../include/cash.h"
#include "../include/state_shop.h"
#include "../include/graph.h"

#include "configReader.h"

int main(int argc, char** argv) {
    // Use smart pointers for automatic memory management
    std::unique_ptr<StateShop> stateShop = std::make_unique<StateShop>();
    std::unique_ptr<Logger> logger = std::make_unique<Logger>(false);

    std::unique_ptr<Manager> rManager = std::make_unique<Manager>(20, logger.get());
    std::unique_ptr<SimulationCore> aManager = std::make_unique<SimulationCore>(rManager.get(), logger.get());

    std::unique_ptr<Customer> rCustomer = std::make_unique<Customer>(stateShop.get(), logger.get());
    std::unique_ptr<Agent> aCustomer = std::make_unique<Agent>(2, aManager.get(), rCustomer.get());
    aManager->registerAgent(aCustomer.get());

    std::unique_ptr<Shop> rShop = std::make_unique<Shop>(4, stateShop.get(), logger.get());
    std::unique_ptr<Agent> aShop = std::make_unique<Agent>(3, aManager.get(), rShop.get());
    aManager->registerAgent(aShop.get());

    std::unique_ptr<Line> rLine = std::make_unique<Line>(stateShop.get(), logger.get());
    std::unique_ptr<Agent> aLine1 = std::make_unique<Agent>(4, aManager.get(), rLine.get());
    std::unique_ptr<Agent> aLine2 = std::make_unique<Agent>(5, aManager.get(), rLine.get());
    aManager->registerAgent(aLine1.get());
    aManager->registerAgent(aLine2.get());

    std::unique_ptr<Cash> rCash1 = std::make_unique<Cash>(std::vector<int>{100, 500, 900}, 50, 80, stateShop.get(), logger.get());
    std::unique_ptr<Cash> rCash2 = std::make_unique<Cash>(std::vector<int>{200, 600, 1000}, 50, 80, stateShop.get(), logger.get());
    std::unique_ptr<Agent> aCash1 = std::make_unique<Agent>(6, aManager.get(), rCash1.get());
    std::unique_ptr<Agent> aCash2 = std::make_unique<Agent>(7, aManager.get(), rCash2.get());
    aManager->registerAgent(aCash1.get());
    aManager->registerAgent(aCash2.get());

    sf::RenderWindow window(sf::VideoMode(800, 600), "Shop Simulation");
    std::unique_ptr<Graph> rGraph = std::make_unique<Graph>(500, window, stateShop.get(), logger.get());
    std::unique_ptr<Agent> aGraph = std::make_unique<Agent>(8, aManager.get(), rGraph.get());
    aManager->registerAgent(aGraph.get());

    aManager->runSimulation();
    logger->addToFile();

    // No need to manually delete anything, since smart pointers take care of that.
    return 0;
}

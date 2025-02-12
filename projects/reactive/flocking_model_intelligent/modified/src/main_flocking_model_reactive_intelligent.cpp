#include "../../../../../library/include/simulationCore.h"

#include "../include/Bird2ReactiveReasoning.h"
#include "../include/Manager1ReactiveReasoning.h"
#include "configReader.h"

int main(int argc, char** argv) {
    srand(time(0)); // Initialize random number generator
    ConfigReader* configReader = new ConfigReader("/home/miska/CLionProjects/Agent_simulation_library/local.cfg");
    // Create a flock of birds
    Logger* logger = new Logger(false);
    int n_birds = 300;
    sf::RenderWindow window(sf::VideoMode(800, 600), "Flocking Simulation");
    Manager1ReactiveReasoning* manager = new Manager1ReactiveReasoning(n_birds, window, logger);
    SimulationCore* simCore = new SimulationCore(manager, logger);
    for (int i = 0; i < n_birds; i++) {
        simCore->registerAgent(new Agent(i + 2, simCore,
                                         new Bird2ReactiveReasoning(3, 0.1, 2.0, 0.25, 0.04, 50.0, n_birds, logger)));
    }

    // Run the simulation
    simCore->runSimulation();
    delete logger;
    return 0;
}
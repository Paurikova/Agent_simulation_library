#include "library/include/simulationCore.h"

#include "simulation_models/reactive/flocking_model_stupid/include/bird.h"
#include "simulation_models/reactive/flocking_model_stupid/include/manager.h"

int main(int argc, char** argv) {
    srand(time(0)); // Initialize random number generator

    // Create a flock of birds
    Logger* logger = new Logger(false);
    int n_birds = 300;
    sf::RenderWindow window(sf::VideoMode(800, 600), "Flocking Simulation");
    Manager* manager = new Manager(3, 0.1, 2.0, 0.25, 0.04, 50.0,
                                   n_birds, window, logger);
    SimulationCore* simCore = new SimulationCore(manager, logger);
    for (int i = 0; i < n_birds; i++) {
        simCore->registerAgent(new Agent(i + 2, simCore,
                                         new Bird(logger)));
    }

    // Run the simulation
    simCore->runSimulation();
    delete logger;
    return 0;
}
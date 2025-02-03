#include "library/include/simulationCore.h"
#include "backend/include//simCoreReactiveReasoning.h"
#include "backend/include/agent1ReactiveReasoning.h"
#include "backend/include/agent2ReactiveReasoning.h"
#include "backend/include/agent3ReactiveReasoning.h"
#include "backend/include/agent1PetriNetReasoning.h"
#include "Obchod_better/manager.h"
#include "Obchod_better/customer.h"
#include "Obchod_better/shop.h"
#include "Obchod_better/line.h"
#include "Obchod_better/cash.h"
#include "flocking_model/bird.h"


#include <iostream>
#include <fstream>
#include <nlohmann/json.hpp>
#include <fstream>

#include <iostream>
#include <string>
#include <vector>
#include <nlohmann/json.hpp>

using json = nlohmann::json;

using namespace nlohmann;

#include <SFML/Graphics.hpp>
#include <vector>
#include <cmath>
#include <cstdlib>
#include <ctime>

const float PI = 3.14159265359;

// Bird class definition
class Bird {
public:
    float x, y;  // Position
    float velX, velY;  // Velocity
    float speed;
    float cohere_factor, separation, separate_factor, match_factor, visual_distance;
    sf::CircleShape shape;

    Bird(float speed, float cohere_factor, float separation, float separate_factor,
         float match_factor, float visual_distance)
            : speed(speed), cohere_factor(cohere_factor), separation(separation),
              separate_factor(separate_factor), match_factor(match_factor),
              visual_distance(visual_distance) {

        // Randomly initialize position and velocity
        x = static_cast<float>(rand() % 500);  // Width of window
        y = static_cast<float>(rand() % 500);  // Height of window
        velX = static_cast<float>(rand() % 2) * 2 - 1;  // Random velocity between -1 and 1
        velY = static_cast<float>(rand() % 2) * 2 - 1;

        shape.setRadius(5);
        shape.setFillColor(sf::Color::White);
        shape.setOrigin(5, 5); // Center the shape at its origin
    }

    // Calculate the Euclidean distance between two birds
    float distance_to(Bird &other) {
        return sqrt((x - other.x) * (x - other.x) + (y - other.y) * (y - other.y));
    }

    // Normalize the velocity (to make it unit length)
    void normalize_velocity() {
        float magnitude = sqrt(velX * velX + velY * velY);
        velX /= magnitude;
        velY /= magnitude;
    }

    // Set the position of the bird on the screen
    void set_position(float x_pos, float y_pos) {
        x = x_pos;
        y = y_pos;
        shape.setPosition(x, y);
    }

    // Function to get the shape for rendering
    sf::CircleShape& get_shape() {
        return shape;
    }
};



// Function to calculate the direction from one bird to another
void calculate_direction(Bird &bird, Bird &neighbor, float &dirX, float &dirY) {
    float dx = neighbor.x - bird.x;
    float dy = neighbor.y - bird.y;
    float magnitude = sqrt(dx * dx + dy * dy);
    dirX = dx / magnitude;
    dirY = dy / magnitude;
}

// Function to simulate a step for each bird
void agent_step(Bird &bird, std::vector<Bird> &birds) {
    std::vector<Bird *> neighbors;

    // Find all neighbors within the visual distance
    for (auto &neighbor : birds) {
        if (&neighbor != &bird && bird.distance_to(neighbor) < bird.visual_distance) {
            neighbors.push_back(&neighbor);
        }
    }

    float matchX = 0, matchY = 0, separateX = 0, separateY = 0, cohereX = 0, cohereY = 0;
    int N = neighbors.size();

    // Calculate the behavior based on neighbors
    for (auto &neighbor : neighbors) {
        float dirX, dirY;
        calculate_direction(bird, *neighbor, dirX, dirY);

        // Cohesion: Move towards the average position of neighbors
        cohereX += dirX;
        cohereY += dirY;

        // Separation: Move away if too close
        if (bird.distance_to(*neighbor) < bird.separation) {
            separateX -= dirX;
            separateY -= dirY;
        }

        // Match: Move in the same direction as neighbors
        matchX += neighbor->velX;
        matchY += neighbor->velY;
    }

    // Normalize the vectors to maintain the same speed
    if (N > 0) {
        cohereX /= N;
        cohereY /= N;
        separateX /= N;
        separateY /= N;
        matchX /= N;
        matchY /= N;
    }

    // Apply the factors to each behavior
    cohereX *= bird.cohere_factor;
    cohereY *= bird.cohere_factor;
    separateX *= bird.separate_factor;
    separateY *= bird.separate_factor;
    matchX *= bird.match_factor;
    matchY *= bird.match_factor;

    // Combine the behaviors
    bird.velX += cohereX + separateX + matchX;
    bird.velY += cohereY + separateY + matchY;

    // Normalize the bird's velocity
    bird.normalize_velocity();

    // Move the bird according to the velocity and speed
    bird.x += bird.velX * bird.speed;
    bird.y += bird.velY * bird.speed;

    // Keep the bird inside the window
    if (bird.x < 0) bird.x = 800;
    if (bird.x > 800) bird.x = 0;
    if (bird.y < 0) bird.y = 600;
    if (bird.y > 600) bird.y = 0;

    bird.shape.setPosition(bird.x, bird.y); // Update bird shape position
}

int main() {
    srand(time(0)); // Initialize random number generator

    // Create a flock of birds
    int n_birds = 300;
    std::vector<Bird> flock;
    for (int i = 0; i < n_birds; ++i) {
        flock.push_back(Bird(0.7, 0.1, 2.0, 0.25, 0.04, 50.0));  // Modify these parameters
    }

    // Create an SFML window
    sf::RenderWindow window(sf::VideoMode(800, 600), "Flocking Simulation");

    // Run the simulation
    while (window.isOpen()) {
        // Handle events
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        // Update bird positions
        for (auto &bird : flock) {
            agent_step(bird, flock);
        }

        // Clear the screen
        window.clear(sf::Color::Black);

        // Draw each bird
        for (auto &bird : flock) {
            window.draw(bird.get_shape());
        }

        // Display everything on the screen
        window.display();
    }

    return 0;
}



//int main(int argc, char** argv) {
////    Manager* manager = new Manager(10, 1);
////    SimulationCore* simCore = new SimulationCore(manager);
////    Customer* cust = new Customer();
////    Agent* aCustomer = new Agent(2, simCore, cust);
////    simCore->registerAgent(aCustomer);
////    Shop* rShop = new Shop(1);
////    Agent* aShop = new Agent(3, simCore, rShop);
////    simCore->registerAgent(aShop);
////    Line* rLineManager1 = new Line();
////    Line* rLineManager2 = new Line();
////    Agent* line1 = new Agent(4, simCore, rLineManager1);
////    Agent* line2 = new Agent(5, simCore, rLineManager2);
////    simCore->registerAgent(line1);
////    simCore->registerAgent(line2);
////    Cash* rCash1 = new Cash({2}, 3, 11);
////    Cash* rCash2 = new Cash({6}, 3, 11);
////    Agent* aCash1 = new Agent(6, simCore, rCash1);
////    Agent* aCash2 = new Agent(7, simCore, rCash2);
////    simCore->registerAgent(aCash1);
////    simCore->registerAgent(aCash2);
////    simCore->runSimulation();
//
//
////    SimCoreReactiveReasoning* simCoreReasoning = new SimCoreReactiveReasoning();
////    SimulationCore* manager = new SimulationCore(simCoreReasoning);
////    Agent1PetriNetReasoning* agent1Reasoning = new Agent1PetriNetReasoning();
////    Agent* agent1 = new Agent(2, manager, agent1Reasoning);
////    manager->registerAgent(agent1);
////    Agent3ReactiveReasoning* agent3Reasoning = new Agent3ReactiveReasoning();
////    Agent* agent3 = new Agent(4, manager, agent3Reasoning);
////    manager->registerAgent(agent3);
////    //ID 2
////    Agent1ReactiveReasoning* agent1Reasoning = new Agent1ReactiveReasoning();
////    Agent* agent1 = new Agent(2, manager, agent1Reasoning);
////    //register agent
////    manager->registerAgent(agent1);
////    Agent2ReactiveReasoning* agent2Reasoning = new Agent2ReactiveReasoning();
////    Agent* agent2 = new Agent(3, agent1, agent2Reasoning);
////    manager->registerAgent(agent2);
//
//
//    //add Message to agent1 schedule
////    Message m1 = {5.,1,1,1,2};
////    manager->pushToMainSchedule(&m1);
////    Message m2 = {2.,1,2,1,-1};
////    manager->pushToMainSchedule(&m2);
////    Message m3 = {4.,2,1,-1,3};
////    manager->pushToMainSchedule(&m3);
//    //run sim
//   // manager->runSimulation();
//
//
//    return 0;
//}
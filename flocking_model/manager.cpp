#include "manager.h"

#include <utility>

// Calculate the Euclidean distance between two birds
float Manager::distance_to(float x1, float y1, float x2, float y2) {
    return sqrt((x1 - x2) * (x1 - x2) + (y1 - y2) * (y1 - y2));
}

// Normalize the velocity (to make it unit length)
void Manager::normalize_velocity(float& velX, float& velY) {
    float magnitude = sqrt(velX * velX + velY * velY);
    velX /= magnitude;
    velY /= magnitude;
}

// Function to calculate the direction from one bird to another
void Manager::calculate_direction(float x1, float y1, float x2, float y2, float &dirX, float &dirY) {
    float dx = x2 - x1;
    float dy = y2 - y1;
    float magnitude = sqrt(dx * dx + dy * dy);
    dirX = dx / magnitude;
    dirY = dy / magnitude;
}

void Manager::registerServices() {
    registerService(1, 1);
    registerService(2, 2);
}

void Manager::registerNodes() {
    registerNode(1, [this](int pSender, int pReceiver, SimTime_t pExecTime, std::unordered_map<std::string, variant_t> args)->NodeId_t {
        return update_positions(pSender, pReceiver, pExecTime, args);
    });
    registerNode(2, [this](int pSender, int pReceiver, SimTime_t pExecTime, std::unordered_map<std::string, variant_t> args)->NodeId_t {
        return move(pSender, pReceiver, pExecTime, args);
    });
};

void Manager::initMessage() {
    // Add implementation of initial message
    // Replace:
    //      pServiceId by required service ID
    //      pExecTime by execution time of event
    //      pReceiver by the ID of the receiving agent
    //open
    sendMessage(1, 0, 1, 2);
}

NodeId_t Manager::update_positions(int pSender, int pReceiver, SimTime_t pExecTime, std::unordered_map<std::string, variant_t> args) {
    birds[curBirdId - 2] = std::move(args);
    if (initRun) {
        updatedPosition += 1;
        if (updatedPosition < number_of_birds) {
            curBirdId += 1;
            sendMessage(1, pReceiver, curBirdId, pExecTime);
            return -1;
        } else {
            curBirdId = 2;
            initRun = false;
        }
    }
    if (curBirdId == number_of_birds + 1) {
        pExecTime += 1;
    }
    sendMessage(2, pReceiver, pSender, pExecTime);
}

NodeId_t  Manager::run() {


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
}

// Function to simulate a step for each bird
NodeId_t Manager::move(int pSender, int pReceiver, SimTime_t pExecTime, std::unordered_map<std::string, variant_t> args) {
    std::vector<NodeId_t> neighbors;
    auto it = birds[curBirdId - 2].find("x");
    float x1 = std::get<float>(it->second);
    it = birds[curBirdId - 2].find("y");
    float y1 = std::get<float>(it->second);
    it = birds[curBirdId - 2].find("velX");
    float velX1 = std::get<float>(it->second);
    it = birds[curBirdId - 2].find("velY");
    float velY1 = std::get<float>(it->second);

    int N = 0;
    // Find all neighbors within the visual distance
    float matchX = 0, matchY = 0, separateX = 0, separateY = 0, cohereX = 0, cohereY = 0;
    for (int i = 2; i <= number_of_birds + 1; i++) {
        if (i != curBirdId) {
            it = birds[curBirdId - 2].find("x");
            float x2 = std::get<float>(it->second);
            it = birds[curBirdId - 2].find("y");
            float y2 = std::get<float>(it->second);
            it = birds[curBirdId - 2].find("velX");
            float velX2 = std::get<float>(it->second);
            it = birds[curBirdId - 2].find("velY");
            float velY2 = std::get<float>(it->second);
            float dist = distance_to(x1, y1, x2, y2);
            if (dist < visual_distance) {
                N += 1;
                // Calculate the behavior based on neighbors
                float dirX, dirY;
                calculate_direction(x1, y1, x2, y2, dirX, dirY);

                // Cohesion: Move towards the average position of neighbors
                cohereX += dirX;
                cohereY += dirY;

                // Separation: Move away if too close
                if (dist < separation) {
                    separateX -= dirX;
                    separateY -= dirY;
                }

                // Match: Move in the same direction as neighbors
                matchX += velX2;
                matchY += velY2;
            }
        }
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
    cohereX *= cohere_factor;
    cohereY *= cohere_factor;
    separateX *= separate_factor;
    separateY *= separate_factor;
    matchX *= match_factor;
    matchY *= match_factor;

    // Combine the behaviors
    velX1 += cohereX + separateX + matchX;
    velY1 += cohereY + separateY + matchY;

    // Normalize the bird's velocity
    normalize_velocity(velX1, velY1);

    // Move the bird according to the velocity and speed
    x1 += velX1 * speed;
    y1 += velY1 * speed;

    // Keep the bird inside the window
    if (x1 < 0) x1 = 800;
    if (x1 > 800) x1 = 0;
    if (y1 < 0) y1 = 600;
    if (y1 > 600) y1 = 0;

    sendMessage(2, pReceiver, curBirdId, pExecTime, -1, std::unordered_map<std::string, variant_t>{
            {"x", x1},
            {"y", y1},
            {"velX", velX1},
            {"velY", velY1}
    });
    curBirdId += 1;
    if (curBirdId > number_of_birds + 1)  {
        curBirdId = 2;
        pExecTime += 1;
    }
    sendMessage(3, pReceiver, pReceiver, pExecTime);
    return -1;
}
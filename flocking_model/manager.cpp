#include "manager.h"

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

void Manager::initialization(int pSender, int pReceiver, SimTime_t pExecTime, State* state) {
    logger->log(fmt::format("{}: update_positions\n", pReceiver));
    StateBird* stateBird = dynamic_cast<StateBird*>(state);
    birds[pSender - 2] = stateBird;
    if (pSender < number_of_birds + 1) {
        return;
    }
    sendMessage(2, pExecTime, pReceiver, pReceiver);
}

void Manager::startWindow(int pSender, int pReceiver, SimTime_t pExecTime, State* state) {
    logger->log(fmt::format("{}: startWindow\n", pReceiver));
    if (window.isOpen()) {
        // Handle events
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
        }
        sendMessage(2, pExecTime, pReceiver, 2);
    }
}

// Function to simulate a step for each bird
void Manager::move(int pSender, int pReceiver, SimTime_t pExecTime, State* state) {
    logger->log(fmt::format("{}: move\n", pReceiver));
    float x1 = birds[pSender-2]->x, y1 = birds[pSender-2]->y, velX1 = birds[pSender-2]->velX, velY1 = birds[pSender-2]->velY;

    int N = 0;
    // Find all neighbors within the visual distance
    float matchX = 0, matchY = 0, separateX = 0, separateY = 0, cohereX = 0, cohereY = 0;
    for (int i = 2; i <= number_of_birds + 1; i++) {
        if (i != pSender) {
            float x2 = birds[i-2]->x, y2 = birds[i-2]->y, velX2 = birds[i-2]->velX, velY2 = birds[i-2]->velY;
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

    StateBird* sendingState = new StateBird(x1, y1, velX1, velY1);

    //update position to bird
    sendMessage(3, pExecTime, pReceiver, pSender, 1, sendingState);
}

void Manager::birdUpdated(int pSender, int pReceiver, SimTime_t pExecTime, State* state) {
    logger->log(fmt::format("{}: birdUpdated\n", pReceiver));
    if (pSender < number_of_birds + 1)  {
        sendMessage(2, pExecTime, pReceiver, pSender + 1);
        return;
    }
    sendMessage(5, pExecTime, pReceiver, pReceiver);
}


void Manager::draw(int pSender, int pReceiver, SimTime_t pExecTime, State* state) {
    logger->log(fmt::format("{}: draw\n", pReceiver));
    // Clear the screen
    window.clear(sf::Color::Black);
    for (int i = 0; i < number_of_birds; i++) {
        shape.setPosition(birds[i]->x, birds[i]->y);
        window.draw(shape);
    }
    // Display everything on the screen
    window.display();
    //Do run again
    sendMessage(2, pExecTime + 1, pReceiver, pReceiver);
}

void Manager::registerFunctions() {
    registerFunction(1, [this](int pSender, int pReceiver, SimTime_t pExecTime, State* state) {
        return initialization(pSender, pReceiver, pExecTime, state);
    });
    registerFunction(2, [this](int pSender, int pReceiver, SimTime_t pExecTime, State* state) {
        return startWindow(pSender, pReceiver, pExecTime, state);
    });
    registerFunction(3, [this](int pSender, int pReceiver, SimTime_t pExecTime, State* state) {
        return move(pSender, pReceiver, pExecTime, state);
    });
    registerFunction(4, [this](int pSender, int pReceiver, SimTime_t pExecTime, State* state) {
        return birdUpdated(pSender, pReceiver, pExecTime, state);
    });
    registerFunction(5, [this](int pSender, int pReceiver, SimTime_t pExecTime, State* state) {
        return draw(pSender, pReceiver, pExecTime, state);
    });
};

void Manager::initMessage() {
    // Add implementation of initial message
    // Replace:
    //      pServiceId by required service ID
    //      pExecTime by execution time of event
    //      pReceiver by the ID of the receiving agent
    //open
    for (int i = 0; i < number_of_birds; i++) {
        sendMessage(1, 0, 1, i+2);
    }
}

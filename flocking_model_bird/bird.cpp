#include "bird.h"

// Calculate the Euclidean distance between two birds
float Bird::distance_to(float x1, float y1, float x2, float y2) {
    return sqrt((x1 - x2) * (x1 - x2) + (y1 - y2) * (y1 - y2));
}

// Normalize the velocity (to make it unit length)
void Bird::normalize_velocity(float& velX, float& velY) {
    float magnitude = sqrt(velX * velX + velY * velY);
    velX /= magnitude;
    velY /= magnitude;
}

// Function to calculate the direction from one bird to another
void Bird::calculate_direction(float x1, float y1, float x2, float y2, float &dirX, float &dirY) {
    float dx = x2 - x1;
    float dy = y2 - y1;
    float magnitude = sqrt(dx * dx + dy * dy);
    dirX = dx / magnitude;
    dirY = dy / magnitude;
}


void Bird::isNeighbor(int pSender, int pReceiver, SimTime_t pExecTime, State* state) {
    logger->log(fmt::format("{}: isNeighbor     [{}]\n", pReceiver, pSender));
    StateBird* neighborState = dynamic_cast<StateBird*>(state);
    // Find all neighbors within the visual distance
    float x2 = neighborState->x, y2 = neighborState->y, velX2 = neighborState->velX, velY2 = neighborState->velY;
    float dist = distance_to(birdState->x, birdState->y, x2, y2);
    if (dist < visual_distance) {
        N += 1;
        // Calculate the behavior based on neighbors
        float dirX, dirY;
        calculate_direction(birdState->x, birdState->y, x2, y2, dirX, dirY);

        // Cohesion: Move towards the average position of neighbors
        stateMove->cohereX += dirX;
        stateMove->cohereY += dirY;

        // Separation: Move away if too close
        if (dist < separation) {
            stateMove->separateX -= dirX;
            stateMove->separateY -= dirY;
        }

        // Match: Move in the same direction as neighbors
        stateMove->matchX += velX2;
        stateMove->matchY += velY2;
    }
    if ((pReceiver != number_of_birds + 1 && pSender < number_of_birds + 1) ||
        (pReceiver == number_of_birds + 1 && pSender < number_of_birds)) {
        return;
    }
    sendMessage(4, pExecTime, pReceiver, pReceiver);
}

void Bird::getPosition(int pSender, int pReceiver, SimTime_t pExecTime, State* state) {
    logger->log(fmt::format("{}: getPosition\n", pReceiver));
    sendMessage(1, pExecTime, pReceiver, pSender, -1, birdState);
}

void Bird::startMove(int pSender, int pReceiver, SimTime_t pExecTime, State* state) {
    logger->log(fmt::format("{}: startMove\n", pReceiver));
    for (int i = 0; i < number_of_birds; i++) {
        if (i + 2 != pReceiver) {
            sendMessage(2, pExecTime, pReceiver, i+2);
        }
    }
}

void Bird::move(int pSender, int pReceiver, SimTime_t pExecTime, State* state) {
    logger->log(fmt::format("{}: move\n", pReceiver));
    // Normalize the vectors to maintain the same speed
    if (N > 0) {
        stateMove->cohereX /= N;
        stateMove->cohereY /= N;
        stateMove->separateX /= N;
        stateMove->separateY /= N;
        stateMove->matchX /= N;
        stateMove->matchY /= N;
    }

    // Apply the factors to each behavior
    stateMove->cohereX *= cohere_factor;
    stateMove->cohereY *= cohere_factor;
    stateMove->separateX *= separate_factor;
    stateMove->separateY *= separate_factor;
    stateMove->matchX *= match_factor;
    stateMove->matchY *= match_factor;

    // Combine the behaviors
    birdState->velX += stateMove->cohereX + stateMove->separateX + stateMove->matchX;
    birdState->velY += stateMove->cohereY + stateMove->separateY + stateMove->matchY;

    // Normalize the bird's velocity
    normalize_velocity(birdState->velX, birdState->velY);

    // Move the bird according to the velocity and speed
    birdState->x += birdState->velX * speed;
    birdState->y += birdState->velY * speed;

    // Keep the bird inside the window
    if (birdState->x < 0) birdState->x = 800;
    if (birdState->x > 800) birdState->x = 0;
    if (birdState->y < 0) birdState->y = 600;
    if (birdState->y > 600) birdState->y = 0;

    N = 0;
    if (pReceiver < number_of_birds + 1) {
        //move another birds
        sendMessage(3, pExecTime, pReceiver, pReceiver + 1);
    } else {
        //display
        sendMessage(3, pExecTime, pReceiver, 1);
    }
}

void Bird::registerFunctions() {
    registerFunction(1, [this](int pSender, int pReceiver, SimTime_t pExecTime, State* state) {
        return isNeighbor(pSender, pReceiver, pExecTime, state);
    });
    registerFunction(2, [this](int pSender, int pReceiver, SimTime_t pExecTime, State* state) {
        return getPosition(pSender, pReceiver, pExecTime, state);
    });
    registerFunction(3, [this](int pSender, int pReceiver, SimTime_t pExecTime, State* state) {
        return startMove(pSender, pReceiver, pExecTime, state);
    });
    registerFunction(4, [this](int pSender, int pReceiver, SimTime_t pExecTime, State* state) {
        return move(pSender, pReceiver, pExecTime, state);
    });
};
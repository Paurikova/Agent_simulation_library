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

//1
NodeId_t Manager::initialization_code1(int pSender, int pReceiver, SimTime_t pExecTime, State* state) {
    logger->log(fmt::format("{}: initialization\n", pReceiver));
    logger->log(fmt::format("initialization_code1\n", pReceiver));
    stateBirds[pSender - 2] = dynamic_cast<StateBird*>(state);
    return 2;
}

//2
NodeId_t Manager::initialization_cond1(int pSender, int pReceiver, SimTime_t pExecTime, State* state) {
    logger->log(fmt::format("initialization_cond1\n", pReceiver));
    if (pSender - 1 != number_of_birds) {
        return 3;
    } else {
        return 4;
    }
}

//3
NodeId_t Manager::initialization_fun1(int pSender, int pReceiver, SimTime_t pExecTime, State* state) {
    logger->log(fmt::format("initialization_fun1\n\n", pReceiver));
    pSender += 1;
    sendMessage(1, pExecTime, pReceiver, pSender);
    return -1;
}

//4
NodeId_t Manager::initialization_fun2(int pSender, int pReceiver, SimTime_t pExecTime, State* state) {
    logger->log(fmt::format("initialization_fun2\n\n", pReceiver));
    sendMessage(3, pExecTime, pReceiver, 2);
    return -1;
}

//5
NodeId_t Manager::isWindowOpen_fun1(int pSender, int pReceiver, SimTime_t pExecTime, State* state) {
    logger->log(fmt::format("{}: isWindowOpen\n", pReceiver));
    logger->log(fmt::format("isWindowOpen_fun1\n\n", pReceiver));
    if (window.isOpen()) {
        sendMessage(4, pExecTime, pSender, pReceiver);
    }
    return -1;
}

//6
NodeId_t Manager::handleEvents_fun1(int pSender, int pReceiver, SimTime_t pExecTime, State* state) {
    logger->log(fmt::format("{}: handleEvents\n", pReceiver));
    logger->log(fmt::format("handleEvents_fun1\n\n", pReceiver));
    // Handle events
    sf::Event event;
    while (window.pollEvent(event)) {
        if (event.type == sf::Event::Closed)
            window.close();
    }
    sendMessage(6, pExecTime, pSender, pReceiver);
    return -1;
}

//7
NodeId_t Manager::move_code1(int pSender, int pReceiver, SimTime_t pExecTime, State* state) {
    logger->log(fmt::format("{}: move\n", pReceiver));
    logger->log(fmt::format("move_code1\n", pReceiver));
    StateMove* helpStateMove = new StateMove();
    return 8;
}

//8
NodeId_t Manager::move_cond1(int pSender, int pReceiver, SimTime_t pExecTime, State* state) {
    logger->log(fmt::format("move_cond1\n", pReceiver));
    StateMove* stateMove = dynamic_cast<StateMove*>(state);
    stateMove->i++;
    if (stateMove->i <= number_of_birds) {
        return 9;
    } else {
        state = stateMove;
        return 11;
    }
}

//9
NodeId_t Manager::move_cond2(int pSender, int pReceiver, SimTime_t pExecTime, State* state) {
    logger->log(fmt::format("move_cond1\n", pReceiver));
    StateMove* stateMove = dynamic_cast<StateMove*>(state);
    if (stateMove->i != pSender) {
        return 10;
    } else {
        state = stateMove;
        return 8;
    }
}


//10
NodeId_t Manager::move_cond2(int pSender, int pReceiver, SimTime_t pExecTime, State* state) {
    logger->log(fmt::format("move_code2\n", pReceiver));
    StateMove* stateMove = dynamic_cast<StateBird*>(state);
    float x1 = stateBirds[pSender - 2]->x, y1 = stateBirds[pSender - 2]->y,
    x2 = stateBirds[stateMove->i - 2]->x, y2 = stateBirds[stateMove->i - 2]->y,
    velX2 = stateBirds[stateMove->i - 2]->x, velY2 = stateBirds[stateMove->i - 2]->y;

    float dist = distance_to(x1, y1, x2, y2);
    if (dist < visual_distance) {
        stateMove->N++;
        // Calculate the behavior based on neighbors
        float dirX, dirY;
        calculate_direction(x1, y1, x2, y2, dirX, dirY);

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
    return 8;
}

//11
NodeId_t Manager::move_code3(int pSender, int pReceiver, SimTime_t pExecTime, State* state) {
    StateMove* stateMove = dynamic_cast<StateBird*>(state);
    // Normalize the vectors to maintain the same speed
    if (stateMove->N > 0) {
        stateMove->cohereX /= stateMove->N;
        stateMove->cohereY /= stateMove->N;
        stateMove->separateX /= stateMove->N;
        stateMove->separateY /= stateMove->N;
        stateMove->matchX /= stateMove->N;
        stateMove->matchY /= stateMove->N;
    }

    // Apply the factors to each behavior
    stateMove->cohereX *= cohere_factor;
    stateMove->cohereY *= cohere_factor;
    stateMove->separateX *= separate_factor;
    stateMove->separateY *= separate_factor;
    stateMove->matchX *= match_factor;
    stateMove->matchY *= match_factor;

    // Combine the behaviors

    float x = stateBirds[pSender-2]->x, y = stateBirds[pSender-2]->y,
    velX = stateBirds[pSender-2]->velX, velY = stateBirds[pSender-2]->velY;
    x += stateMove->cohereX + stateMove->separateX + stateMove->matchX;
    stateBirds[pSender-2]->velY += stateMove->cohereY + stateMove->separateY + stateMove->matchY;

    // Normalize the bird's velocity
    normalize_velocity(stateBirds[pSender-2]->velX, stateBirds[pSender-2]->velY);

    // Move the bird according to the velocity and speed
    stateBirds[pSender-2]->x += stateBirds[pSender-2]->velX * speed;
    stateBirds[pSender-2]->y += stateBirds[pSender-2]->velY * speed;

    // Keep the bird inside the window
    if (stateBirds[pSender-2]->x < 0) stateBirds[pSender-2]->x = 800;
    if (stateBirds[pSender-2]->x > 800) stateBirds[pSender-2]->x = 0;
    if (stateBirds[pSender-2]->y < 0) stateBirds[pSender-2]->y = 600;
    if (stateBirds[pSender-2]->y > 600) stateBirds[pSender-2]->y = 0;

    //move bird
    sendMessage(1, pExecTime, pReceiver, curBirdId, 1, state);
    return -1;

}
//8
NodeId_t Manager::move_code1(int pSender, int pReceiver, SimTime_t pExecTime, State* state) {
    logger->log(fmt::format("{}: move\n", pReceiver));
    logger->log(fmt::format("move_cond1\n", pReceiver));

    int N = 0;
    // Find all neighbors within the visual distance

    float matchX = 0, matchY = 0, separateX = 0, separateY = 0, cohereX = 0, cohereY = 0;
    for (int i = 2; i <= number_of_birds + 1; i++) {
        if (i != curBirdId) {
            it = birds[i - 2].find("x");
            float x2 = std::get<float>(it->second);
            it = birds[i - 2].find("y");
            float y2 = std::get<float>(it->second);
            it = birds[i - 2].find("velX");
            float velX2 = std::get<float>(it->second);
            it = birds[i - 2].find("velY");
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
    velX1 += cohereX + separateX + matchX;// Normalize the vectors to maintain the same speed
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

    std::unordered_map<std::string, variant_t> newArgs = {
            {"x", x1},
            {"y", y1},
            {"velX", velX1},
            {"velY", velY1}
    };

    //update current positions
    birds[curBirdId - 2] = newArgs;
    //update position to bird
    sendMessage(2, pExecTime, pReceiver, curBirdId, 1, newArgs);
    return -1;
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

    std::unordered_map<std::string, variant_t> newArgs = {
            {"x", x1},
            {"y", y1},
            {"velX", velX1},
            {"velY", velY1}
    };

    //update current positions
    birds[curBirdId - 2] = newArgs;
    //update position to bird
    sendMessage(2, pExecTime, pReceiver, curBirdId, 1, newArgs);
    return -1;
}

//7
NodeId_t Manager::move_cond1(int pSender, int pReceiver, SimTime_t pExecTime, State* state) {
    logger->log(fmt::format("{}: move\n", pReceiver));
    logger->log(fmt::format("move_cond1\n\n", pReceiver));
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
            it = birds[i - 2].find("x");
            float x2 = std::get<float>(it->second);
            it = birds[i - 2].find("y");
            float y2 = std::get<float>(it->second);
            it = birds[i - 2].find("velX");
            float velX2 = std::get<float>(it->second);
            it = birds[i - 2].find("velY");
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

    std::unordered_map<std::string, variant_t> newArgs = {
            {"x", x1},
            {"y", y1},
            {"velX", velX1},
            {"velY", velY1}
    };

    //update current positions
    birds[curBirdId - 2] = newArgs;
    //update position to bird
    sendMessage(2, pExecTime, pReceiver, curBirdId, 1, newArgs);
    return -1;
}

//7
NodeId_t Manager::move_code1(int pSender, int pReceiver, SimTime_t pExecTime, State* state) {
    logger->log(fmt::format("move_code1\n\n", pReceiver));
    StateBird* stateBird = dynamic_cast<StateBird*>(state);
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



//8
NodeId_t Manager::move_code1(int pSender, int pReceiver, SimTime_t pExecTime, State* state) {
    logger->log(fmt::format("move_code1\n", pReceiver));

    it = birds[curBirdId - 2].find("x");
    float x1 = std::get<float>(it->second);
    it = birds[curBirdId - 2].find("y");
    float y1 = std::get<float>(it->second);
    it = birds[curBirdId - 2].find("velX");
    float velX1 = std::get<float>(it->second);
    it = birds[curBirdId - 2].find("velY");
    float velY1 = std::get<float>(it->second);

    it = birds[i - 2].find("x");
    float x2 = std::get<float>(it->second);
    it = birds[i - 2].find("y");
    float y2 = std::get<float>(it->second);
    it = birds[i - 2].find("velX");
    float velX2 = std::get<float>(it->second);
    it = birds[i - 2].find("velY");
    float velY2 = std::get<float>(it->second);
    float dist = distance_to(x1, y1, x2, y2);


    it = birds[curBirdId - 2].find("x");
    float x1 = std::get<float>(it->second);
    it = birds[curBirdId - 2].find("y");
    float y1 = std::get<float>(it->second);
    it = birds[curBirdId - 2].find("velX");
    float velX1 = std::get<float>(it->second);
    it = birds[curBirdId - 2].find("velY");
    float velY1 = std::get<float>(it->second);

    it = birds[i - 2].find("x");
    float x2 = std::get<float>(it->second);
    it = birds[i - 2].find("y");
    float y2 = std::get<float>(it->second);
    it = birds[i - 2].find("velX");
    float velX2 = std::get<float>(it->second);
    it = birds[i - 2].find("velY");
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

    std::unordered_map<std::string, variant_t> newArgs = {
            {"x", x1},
            {"y", y1},
            {"velX", velX1},
            {"velY", velY1}
    };

    //update current positions
    birds[curBirdId - 2] = newArgs;
    //update position to bird
    sendMessage(2, pExecTime, pReceiver, curBirdId, 1, newArgs);
    return -1;
}


//7
NodeId_t Manager::move_code(int pSender, int pReceiver, SimTime_t pExecTime, State* state) {

    auto it = args.find("matchX");
    if (it != args.end()) float matchX = std::get<float>(it->second);
    it = args.find("matchY");
    if (it != args.end()) float matchY = std::get<float>(it->second);
    it = args.find("separateX");
    if (it != args.end()) float separateX = std::get<float>(it->second);
    it = args.find("separateY");
    if (it != args.end()) float separateY = std::get<float>(it->second);
    it = args.find("cohereX");
    if (it != args.end()) float cohereX = std::get<float>(it->second);
    it = args.find("cohereY");
    if (it != args.end()) float cohereY = std::get<float>(it->second);
    it = args.find("N");
    if (it != args.end()) float cohereX = std::get<float>(it->second);
    it = args.find("i");
    if (it != args.end()) float cohereY = std::get<float>(it->second);

    logger->log(fmt::format("{}: move\n", pReceiver));
    logger->log(fmt::format("handleEvents_fun1\n\n", pReceiver));
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
            it = birds[i - 2].find("x");
            float x2 = std::get<float>(it->second);
            it = birds[i - 2].find("y");
            float y2 = std::get<float>(it->second);
            it = birds[i - 2].find("velX");
            float velX2 = std::get<float>(it->second);
            it = birds[i - 2].find("velY");
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

    std::unordered_map<std::string, variant_t> newArgs = {
            {"x", x1},
            {"y", y1},
            {"velX", velX1},
            {"velY", velY1}
    };

    //update current positions
    birds[curBirdId - 2] = newArgs;
    //update position to bird
    sendMessage(2, pExecTime, pReceiver, curBirdId, 1, newArgs);
    return -1;
}


void Manager::registerServices() {
    registerService(1, 1);
    registerService(2, 2);
    registerService(3, 3);
    registerService(4, 4);
    registerService(5, 5);
    registerService(6, 6);
    registerService(7, 7);
}

void Manager::registerNodes() {
    registerNode(1, [this](int pSender, int pReceiver, SimTime_t pExecTime, State* state)->NodeId_t {
        return update_positions(pSender, pReceiver, pExecTime, args);
    });
    registerNode(2, [this](int pSender, int pReceiver, SimTime_t pExecTime, State* state)->NodeId_t {
        return move(pSender, pReceiver, pExecTime, args);
    });
    registerNode(3, [this](int pSender, int pReceiver, SimTime_t pExecTime, State* state)->NodeId_t {
        return isWindowOpen(pSender, pReceiver, pExecTime, args);
    });
    registerNode(4, [this](int pSender, int pReceiver, SimTime_t pExecTime, State* state)->NodeId_t {
        return handle_events(pSender, pReceiver, pExecTime, args);
    });
    registerNode(5, [this](int pSender, int pReceiver, SimTime_t pExecTime, State* state)->NodeId_t {
        return clearScreen(pSender, pReceiver, pExecTime, args);
    });
    registerNode(6, [this](int pSender, int pReceiver, SimTime_t pExecTime, State* state)->NodeId_t {
        return display(pSender, pReceiver, pExecTime, args);
    });
    registerNode(7, [this](int pSender, int pReceiver, SimTime_t pExecTime, State* state)->NodeId_t {
        return bird_updated(pSender, pReceiver, pExecTime, args);
    });
};

void Manager::initMessage() {
    // Add implementation of initial message
    // Replace:
    //      pServiceId by required service ID
    //      pExecTime by execution time of event
    //      pReceiver by the ID of the receiving agent
    //open
    sendMessage(3, 0, 1, 1);
}

NodeId_t Manager::bird_updated(int pSender, int pReceiver, SimTime_t pExecTime, State* state) {
    //std::cout << pReceiver << ": bird_updated [" << pSender << "]" << std::endl;
    curBirdId += 1;
    if (curBirdId > number_of_birds + 1)  {
        curBirdId = 2;
        sendMessage(5, pExecTime, pReceiver, pReceiver);
        return -1;
    }
    sendMessage(2, pExecTime, pReceiver, pReceiver);
    return -1;
}

NodeId_t Manager::clearScreen(int pSender, int pReceiver, SimTime_t pExecTime, State* state) {
    //std::cout << pReceiver << ": clearScreen" << std::endl;
    // Clear the screen
    window.clear(sf::Color::Black);
    for (int i = 0; i < number_of_birds; i++) {
        sendMessage(3, pExecTime, pReceiver, i + 2);
    }
    return -1;
}

NodeId_t Manager::display(int pSender, int pReceiver, SimTime_t pExecTime, State* state) {
    //std::cout << pReceiver << ": display";
    if (pSender - 1 == number_of_birds) {
        //std::cout << "      YES" << std::endl;
        // Display everything on the screen
        window.display();
        //Do run again
        sendMessage(3, pExecTime + 1, pReceiver, pReceiver);
    } else {
        //std::cout << "      NO" << std::endl;
    }
    return -1;
}


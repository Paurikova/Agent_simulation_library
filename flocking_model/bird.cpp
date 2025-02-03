#include "bird.h"

NodeId_t Bird::move(int pSender, int pReceiver, SimTime_t pExecTime, std::unordered_map<std::string, std::variant<int, float, std::string, std::vector<float>>> args) {
    x += velX;
    y += velY;

    // Keep the agent inside the screen boundaries
    if (x < 0) x = screenX;
    if (x > screenX) x = 0;
    if (y < 0) y = screenY;
    if (y > screenY) y = 0;

    shape.setPosition(x, y);  // Update shape position
    return -1;
}

NodeId_t Bird::getAttributes(int pSender, int pReceiver, SimTime_t pExecTime, std::unordered_map<std::string, std::variant<int, float, std::string, std::vector<float>>> args) {
    sendMessage(1,  pExecTime, pReceiver, pSender, -1, std::unordered_map<std::string, std::variant<int, float, std::string, std::vector<float>>>{
            {"x", x},
            {"y", y},
            {"velX", velX},
            {"velY", velY}
    });
    return -1;
}

NodeId_t Bird::isNeighbors(int pSender, int pReceiver, SimTime_t pExecTime,
                           std::unordered_map<std::string, std::variant<int, float, std::string, std::vector<float>>> args) {
    auto it = args.find("x");
    int otherX = std::get<float>(it->second);
    it = args.find("y");
    int otherY = std::get<float>(it->second);
    bool result = false;
    if (distance_to(otherX, otherY) < visual_distance) {
        result = true;
    }
    sendMessage(2,  pExecTime, pReceiver, pSender, -1, std::unordered_map<std::string, std::variant<int, float, std::string, std::vector<float>>>{
            {"isNeighbors", result}
    });
}

float Bird::distance_to(float otherX, float otherY) {
    return sqrt((x - otherX) * (x - otherX) + (y - otherY) * (y - otherY));
}

NodeId_t Bird::normalize_velocity(int pSender, int pReceiver, SimTime_t pExecTime, std::unordered_map<std::string, std::variant<int, float, std::string, std::vector<float>>> args) {
    float magnitude = sqrt(velX * velX + velY * velY);
    velX /= magnitude;
    velY /= magnitude;
    return {};
}

void Bird::registerNodes() {
    // Register nodes as callbacks, with each node returning a deque<NodeId_t>
    registerNode(1, [this](int pSender, int pReceiver, SimTime_t pExecTime, std::unordered_map<std::string, std::variant<int, float, std::string, std::vector<float>>> args) -> NodeId_t {
        return move(pSender, pReceiver, pExecTime, args);  // move returns empty deque, if needed return data
    });
    registerNode(2, [this](int pSender, int pReceiver, SimTime_t pExecTime, std::unordered_map<std::string, std::variant<int, float, std::string, std::vector<float>>> args) -> NodeId_t {
        return getAttributes(pSender, pReceiver, pExecTime, args);  // getPositionX returns deque with x position
    });
    registerNode(4, [this](int pSender, int pReceiver, SimTime_t pExecTime, std::unordered_map<std::string, std::variant<int, float, std::string, std::vector<float>>> args) -> NodeId_t {
        return normalize_velocity(pSender, pReceiver, pExecTime, args);  // normalize_velocity returns empty deque
    });
}

void Bird::registerServices() {
    registerService(1, 1);
    registerService(2, 2);
    registerService(3, 3);
    registerService(4, 4);
}

// Function to get the shape for rendering
sf::CircleShape& Bird::get_shape() {
    return shape;
}

// Flocking behavior
void Bird::flock(int pSender, int pReceiver, SimTime_t pExecTime, std::unordered_map<std::string, std::variant<int, float, std::string, std::vector<float>>> args) {
    std::vector<Agent *> neighbors;

    // Find all neighbors within the visual distance
    for (auto &agent : agents) {
        if (&agent != this && distance_to(agent) < visual_distance) {
            neighbors.push_back(&agent);
        }
    }

    float matchX = 0, matchY = 0, separateX = 0, separateY = 0, cohereX = 0, cohereY = 0;
    std::vector<float> neighborsX, neighborsY, neighborsVelX, neighborsVelY;
    auto itX = std::get_if<std::vector<float>>(&args["neighborsX"]);
    neighborsX = *itX;
    auto itY = std::get_if<std::vector<float>>(&args["neighborsY"]);
    neighborsY = *itY;
    auto itVelX = std::get_if<std::vector<float>>(&args["neighborsVelX"]);
    neighborsVelX = *itVelX;
    auto itVelY = std::get_if<std::vector<float>>(&args["neighborsVelY"]);
    neighborsVelY = *itVelY;
    int N = neighborsX.size();
    for (int i; i < N; i++) {
        float dx = neighborsX[i] - x;
        float dy = neighborsY[i] - y;
        float magnitude = sqrt(dx * dx + dy * dy);
        float dirX = dx / magnitude;
        float dirY = dy / magnitude;

        // Cohesion: Move towards the average position of neighbors
        cohereX += dirX;
        cohereY += dirY;

        // Separation: Move away if too close
        if (distance_to(neighborsX[i], neighborsY[i]) < separation) {
            separateX -= dirX;
            separateY -= dirY;
        }

        // Match: Move in the same direction as neighbors
        matchX += neighbor->velX;
        matchY += neighbor->velY;
    }
    // Calculate the behavior based on neighbors
    for (auto &neighbor : neighbors) {
        float dx = neighbor->x - x;
        float dy = neighbor->y - y;
        float magnitude = sqrt(dx * dx + dy * dy);
        float dirX = dx / magnitude;
        float dirY = dy / magnitude;

        // Cohesion: Move towards the average position of neighbors
        cohereX += dirX;
        cohereY += dirY;

        // Separation: Move away if too close
        if (distance_to(*neighbor) < separation) {
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
    cohereX *= cohere_factor;
    cohereY *= cohere_factor;
    separateX *= separate_factor;
    separateY *= separate_factor;
    matchX *= match_factor;
    matchY *= match_factor;

    // Combine the behaviors
    velX += cohereX + separateX + matchX;
    velY += cohereY + separateY + matchY;

    // Normalize the agent's velocity
    normalize_velocity();
}
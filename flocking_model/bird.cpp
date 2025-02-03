#include "bird.h"

NodeId_t Bird::move(std::unordered_map<std::string, std::variant<int, double, std::string>> args) {
    x += velX;
    y += velY;

    // Keep the agent inside the screen boundaries
    if (x < 0) x = 800;
    if (x > 800) x = 0;
    if (y < 0) y = 600;
    if (y > 600) y = 0;

    shape.setPosition(x, y);  // Update shape position
    return {};
}

NodeId_t Bird::getPositionX(std::unordered_map<std::string, std::variant<int, double, std::string>> args) {
    return {};
}

NodeId_t Bird::getPositionY(std::unordered_map<std::string, std::variant<int, double, std::string>> args) {
    return {};
}
NodeId_t Bird::normalize_velocity(std::unordered_map<std::string, std::variant<int, double, std::string>> args) {
    float magnitude = sqrt(velX * velX + velY * velY);
    velX /= magnitude;
    velY /= magnitude;
    return {};
}

void Bird::registerNodes() {
    // Register nodes as callbacks, with each node returning a deque<NodeId_t>
    registerNode(1, [this](std::unordered_map<std::string, std::variant<int, double, std::string>> args) -> NodeId_t {
        return move(args);  // move returns empty deque, if needed return data
    });
    registerNode(2, [this](std::unordered_map<std::string, std::variant<int, double, std::string>> args) -> NodeId_t {
        return getPositionX(args);  // getPositionX returns deque with x position
    });
    registerNode(3, [this](std::unordered_map<std::string, std::variant<int, double, std::string>> args) -> NodeId_t {
        return getPositionY(args);  // getPositionY returns deque with y position
    });
    registerNode(4, [this](std::unordered_map<std::string, std::variant<int, double, std::string>> args) -> NodeId_t {
        return normalize_velocity(args);  // normalize_velocity returns empty deque
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
void Bird::flock(std::unordered_map<std::string, std::variant<int, double, std::string>> args) {
    std::vector<Agent *> neighbors;

    // Find all neighbors within the visual distance
    for (auto &agent : agents) {
        if (&agent != this && distance_to(agent) < visual_distance) {
            neighbors.push_back(&agent);
        }
    }

    float matchX = 0, matchY = 0, separateX = 0, separateY = 0, cohereX = 0, cohereY = 0;
    int N = neighbors.size();

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
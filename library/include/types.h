using AgentId_t = int; // type for agent ID
using ServiceId_t = int; // type for service ID
using SimTime_t = float; // type for simulation time
using ExecFunct_t = std::function<void(int)>; // type for function callback

namespace {
    const SimTime_t SIMULATION_TIME_OFFSET = 0;

// Static counter for the next agent ID
    int nextAgentId = 1;
// Static counter for the next message ID
    int nextMessageId = 1;
}
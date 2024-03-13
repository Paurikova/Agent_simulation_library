#include "types.h"
const SimTime_t SIMULATION_TIME_STEP = 1;
const SimTime_t SIMULATION_TIME_OFFSET = 0;

using AgentId_t = int; // type for agent ID
using ServiceId_t = int; // type for service ID
using SimTime_t = float; // type for simulation time
using ExecFunct_t = std::function<void(int)>; // type for function callback

// Static counter for the next agent ID
static int nextAgentId = 1;
// Static counter for the next message ID
static int nextMessageId = 1;
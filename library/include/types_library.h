#pragma once
#include <string>
#include <functional>
#include <deque>

#include "state.h"

using AgentId_t = int; // type for agent ID
using ServiceId_t = int; // type for service ID
using SimTime_t = float; // type for simulation time
using NodeId_t = int;
using ExecFunct_t = std::function<void(int, int, SimTime_t, State*)>; // type for function callback
using ExecNode_t = std::function<NodeId_t(int, int, SimTime_t, State*)>; // type for function callback

const AgentId_t MAIN_AGENT_ID = 1;
const NodeId_t UNDEFINATED_NODE =  -1;

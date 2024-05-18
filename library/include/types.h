#pragma once
#include <string>
#include <functional>

using AgentId_t = int; // type for agent ID
using ServiceId_t = int; // type for service ID
using SimTime_t = float; // type for simulation time
using ExecFunct_t = std::function<void(int, SimTime_t)>; // type for function callback

//enum class AgentType {REACTIVE, INTELLIGENT};

const AgentId_t SIMULATION_CORE_ID = 1;
const AgentId_t REASONING_ID_START = 2;

